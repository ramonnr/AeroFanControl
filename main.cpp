#include <QApplication>
//#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QQuickStyle>
#include "ec.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterSingletonType(QUrl("qrc:///Style.qml"),"Style",1,0,"Style");
    //qmlRegisterUncreatableType<FanModes::Mode>("myfan",1,0,"FanState","enum, uncreatable");
    //qmlRegisterUncreatableMetaObject(FanStates::staticMetaObject,"com.whatevs",1,0,"FanState","Cant create Enum!!");
    qmlRegisterUncreatableType<FanState>("FanState",1,0,"FanState","Enum only");
    QApplication app(argc, argv);
    //QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    EC ec;
    engine.rootContext()->setContextProperty("ECData",&ec);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
