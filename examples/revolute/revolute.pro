TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

target.path = $$[QT_INSTALL_EXAMPLES]/Box2D/$${TARGET}/
export(target.path)
INSTALLS += target
export(INSTALLS)
OTHER_FILES += doc/revolute-examples.qdoc
