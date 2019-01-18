#ifndef EC_H
#define EC_H

#include <QObject>
#include <QFile>
#include <mutex>

class FanState : public QObject{
    Q_OBJECT
public:
    enum class State{
        Silent,
        Normal,
        Cool
    };
    Q_ENUM(State)
};

class EC : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList modelHex MEMBER m_valuesHex NOTIFY modelChanged)
    Q_PROPERTY(FanState::State mode MEMBER m_mode NOTIFY modeChanged)
public:
    EC(QObject* parent = nullptr);
    ~EC();
    const std::array<uint8_t, 256> read();
    void write(uint8_t, uint8_t);
    QStringList getECData(void);
    void envCheck(void);
    Q_INVOKABLE void setSilent();
    Q_INVOKABLE void setNormal();
    Q_INVOKABLE void setCool();
signals:
    void modelChanged(void);
    void modeChanged(void);
    void fanSpeed(int fan, int speed);
    void cpuTemp(int temp);
    void warning(QString title, QString body);
private:
    void setMode(const FanState::State&);
    void update(void);
    QStringList m_valuesHex;
    QFile m_ecFile;
    bool m_killSignal = false;
    bool m_silent = false;
    bool m_normal = false;
    bool m_cool = false;
    FanState::State m_mode = FanState::State::Normal;
    std::mutex m_mut;
};


#endif // EC_H
