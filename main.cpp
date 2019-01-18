#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ec.h"
#include "qmlsingleton.h"
#include <QDebug>

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterSingletonType(QUrl("qrc:///Style.qml"),"Style",1,0,"Style");
    qmlRegisterUncreatableType<FanState>("FanState",1,0,"FanState","Enum only");
    QApplication app(argc, argv);

    EC ec;
    QmlSingleton::instance().rootContext()->setContextProperty("ECData",&ec);
    QmlSingleton::openWindow(QUrl(QStringLiteral("qrc:/main.qml")));

    if (QmlSingleton::instance().rootObjects().isEmpty()){
        return -1;
    }
    ec.envCheck();
    return app.exec();
}
