#include "ec.h"
#include <thread>
#include <chrono>
#include <QDebug>
EC::EC(QObject* parent):  QObject(parent){
    m_ecFile.setFileName("/sys/kernel/debug/ec/ec0/io");
    for(auto i = 0; i < 256; i++){
        m_valuesHex.push_back(QString(i));
        m_valuesUtf.push_back(QString(i));
    }
    std::thread([this]{update();}).detach();
}

EC::~EC(){
    m_killSignal = true;
}


QStringList EC::getECData(void){
    return m_valuesHex;
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
            m_valuesUtf[i] = rbuf.at(i);
            //filter garbage
            if(m_valuesHex[i].size() > 2){
                m_valuesHex[i] = "" + m_valuesHex[i][m_valuesHex[i].size()-2] + m_valuesHex[i][m_valuesHex[i].size()-1];
            }
        }
        emit modelChanged();
        std::this_thread::sleep_for(std::chrono::milliseconds(1100));
    }
}
