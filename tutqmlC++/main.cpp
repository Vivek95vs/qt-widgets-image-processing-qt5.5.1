#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "myqt.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MYqt mycontrol;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mycontrol", &mycontrol);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

