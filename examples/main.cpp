#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QtQml>
#include <box2dplugin.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Box2DPlugin plugin;
    plugin.registerTypes("Box2D");

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/ui.qml"));

    return app.exec();
}

