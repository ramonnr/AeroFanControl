#ifndef QMLSINGLETON_H
#define QMLSINGLETON_H
#include <QQmlApplicationEngine>
#include <QQmlEngine>

class QmlSingleton{
public:
    QmlSingleton(QmlSingleton const&) = delete;
    void operator=(QmlSingleton const&) = delete;
    static QQmlApplicationEngine& instance(){
        static QQmlApplicationEngine qengine;
        return qengine;
    }
    static void openWindow(const QUrl& url){
        instance().load(url);
    }
private:
    QmlSingleton(){}
};

#endif // QMLSINGLETON_H
