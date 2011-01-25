# Include this file in your .pro file to statically compile the Box2D QML
# bindings into your project.
#
# Basic usage instructions:
#
#  #include <box2dplugin.h>
#
#  int main(int argc, char *argv[])
#  {
#      QApplication app(argc, argv);
#
#      Box2DPlugin plugin;
#      plugin.registerTypes("Box2D");
#
#      ...
#  }

INCLUDEPATH += $$PWD
include(Box2D/box2d.pri)

SOURCES += $$PWD/box2dplugin.cpp \
    $$PWD/box2dworld.cpp \
    $$PWD/box2dbody.cpp \
    $$PWD/box2dfixture.cpp \
    $$PWD/box2ddebugdraw.cpp

HEADERS += \
    $$PWD/box2dplugin.h \
    $$PWD/box2dworld.h \
    $$PWD/box2dbody.h \
    $$PWD/box2dfixture.h \
    $$PWD/box2ddebugdraw.h
