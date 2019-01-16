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
    if(!m_ecFile.isOpen()){
        m_ecFile.open(QIODevice::WriteOnly | QIODevice::Append);
    }
    const uint8_t offset = [&]{
        if(nextMode == FanState::State::Silent)return static_cast<uint8_t>(0x08);
        else if(nextMode == FanState::State::Normal)return static_cast<uint8_t>(0x08);
        else return static_cast<uint8_t>(0x09);
    }();
    m_ecFile.seek(offset);
    const uint8_t writeVal = [&]{
        if(nextMode == FanState::State::Silent){
            return uint8_t{0x40};
        }
        else{
            return uint8_t{0};
        }
    }();
    QDataStream qs(&m_ecFile);
    qs << writeVal;
    m_ecFile.close();
}

void EC::update(){
    while(!m_killSignal){
        if(!m_ecFile.isOpen()){
            m_ecFile.open(QIODevice::ReadOnly);
        }
        QByteArray rbuf = m_ecFile.readAll();
        m_ecFile.close();
        for(auto i = 0; i < qMin(m_valuesHex.size(),rbuf.size()); i++){
            m_valuesHex[i] = QString::number(static_cast<int>(rbuf[i]),16).toUpper();
            //filter garbage
            if(m_valuesHex[i].size() > 2){
                m_valuesHex[i] = "" + m_valuesHex[i][m_valuesHex[i].size()-2] + m_valuesHex[i][m_valuesHex[i].size()-1];
            }
        }
        auto prevMode = m_mode;
        //check modes
        if( (rbuf[8] & 0x40) != 0){
            m_mode = FanState::State::Silent;
        }else{
            m_mode = FanState::State::Normal;
        }
        if(prevMode != m_mode){emit modeChanged();}
        //this one will change on every run, don't bother checking for is actual change
        emit modelChanged();
        std::this_thread::sleep_for(std::chrono::milliseconds(1100));
    }
}
