#include "ec.h"
#include <thread>
#include <chrono>
#include <QDataStream>
#include <QDebug>
EC::EC(QObject* parent):  QObject(parent){
    m_ecFile.setFileName("/sys/kernel/debug/ec/ec0/io");
    for(auto i = 0; i < 256; i++){
        m_valuesHex.push_back(QString(i));
    }
    std::thread([this]{update();}).detach();
}

EC::~EC(){
    m_killSignal = true;
}

void EC::envCheck(void){
    if(!m_ecFile.exists()){
        emit warning("Unexpected environment",
                     "Embedded controller file not found\n"
                     "This program must run with root privileges\n"
                     "Are you sure this is an Aero machine running linux?\n"
                     "The program will still run, it's just not going to do anything meaningful");
    }

}

QStringList EC::getECData(void){
    return m_valuesHex;
}

void EC::setSilent(){
    setMode(FanState::State::Silent);
}

void EC::setNormal(){
    setMode(FanState::State::Normal);
}

void EC::setCool(){
    setMode(FanState::State::Cool);
}

void EC::setMode(const FanState::State& nextMode){
    if(m_mode == nextMode) {return;}
    if(!m_ecFile.exists()) {return;}
    std::lock_guard<std::mutex> lck(m_mut);
    if(m_ecFile.isOpen()){
        m_ecFile.close();
    }
    m_ecFile.open(QIODevice::WriteOnly | QIODevice::Append);

    //there are to bytes of interest, offst 0x08 and 0x0C
    //for silent 0x08 := 0x40 & 0x0C := 0x0
    //for normal 0x08 := 0x0  & 0x0C := 0x0
    //for cool   0x08 := 0x0  & 0x0C := 0x90
    const quint8 silentOffset = 0x08;
    const quint8 coolOffset   = 0x0C;
    m_ecFile.seek(silentOffset);
    QDataStream qs(&m_ecFile);
    if(nextMode == FanState::State::Silent){
        qs << quint8{0x40};
    }
    else{
        qs << quint8{0x00};
    }
    m_ecFile.seek(coolOffset);
    if(nextMode == FanState::State::Cool){
        qs << quint8{0x90};
    }
    else{
        qs << quint8{0x00};
    }
    m_ecFile.close();
}

void EC::update(){
    if(!m_ecFile.exists()){return;}
    while(!m_killSignal){
        QByteArray rbuf;
        {
            std::lock_guard<std::mutex> lck(m_mut);
            if(m_ecFile.isOpen()){
                m_ecFile.close();
            }
            m_ecFile.open(QIODevice::ReadOnly);
            rbuf = m_ecFile.readAll();
            m_ecFile.close();
        }
        for(auto i = 0; i < qMin(m_valuesHex.size(),rbuf.size()); i++){
            m_valuesHex[i] = QString::number(static_cast<quint8>(rbuf[i]),16).toUpper();
        }

        auto silentSet = [&]()->bool{return static_cast<quint8>(rbuf[0x08]) == static_cast<quint8>(0x40);};
        auto coolSet   = [&]()->bool{return static_cast<quint8>(rbuf[0x0C]) == static_cast<quint8>(0x90);};
        auto prevMode = m_mode;
        //check modes
        if(silentSet() && !coolSet())       {m_mode = FanState::State::Silent;}
        else if(!silentSet() && !coolSet()) {m_mode = FanState::State::Normal;}
        else if(!silentSet() && coolSet())  {m_mode = FanState::State::Cool;}
        else                                {/*I just dont know man*/}
        if(prevMode != m_mode){emit modeChanged();}
        //update fangraph
        //each fan is usgin 2B, fan 0 -> [0xFC,0xFD], fan 1 -> [0xFE,0xFF]
        emit fanSpeed(0,(m_valuesHex[0xFC] + m_valuesHex[0xFD]).toInt(nullptr,16));
        emit fanSpeed(1,(m_valuesHex[0xFE] + m_valuesHex[0xFF]).toInt(nullptr,16));
        emit cpuTemp(m_valuesHex[0x60].toInt(nullptr,16));
        emit modelChanged();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}
