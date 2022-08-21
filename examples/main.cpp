#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QtQml>
#include <box2dplugin.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Box2DPlugin plugin;
    plugin.registerTypes("Box2D");
    qmlProtectModule("Box2D", 2);

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/ui.qml"));

    return app.exec();
}

