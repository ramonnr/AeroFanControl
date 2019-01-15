#ifndef EC_H
#define EC_H

#include <QObject>
#include <QFile>
class EC : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList modelHex MEMBER m_valuesHex NOTIFY modelChanged)
    Q_PROPERTY(QStringList modelUtf MEMBER m_valuesUtf NOTIFY modelChanged)
public:
    EC(QObject* parent = nullptr);
    ~EC();
    const std::array<uint8_t, 256> read();
    void write(uint8_t, uint8_t);
    QStringList getECData(void);
signals:
    void modelChanged(void);
private:
    void update(void);
    QStringList m_valuesHex;
    QStringList m_valuesUtf;
    QFile m_ecFile;
    bool m_killSignal = false;
};


#endif // EC_H
