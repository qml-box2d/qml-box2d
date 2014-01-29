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
    $$PWD/box2ddebugdraw.cpp \
    $$PWD/box2djoint.cpp \
    $$PWD/box2drevolutejoint.cpp \
    $$PWD/box2ddistancejoint.cpp \
    $$PWD/box2dprismaticjoint.cpp \
    $$PWD/box2ddestructionlistener.cpp \
    $$PWD/box2dmotorjoint.cpp \
    $$PWD/box2dweldjoint.cpp \
    $$PWD/box2dpulleyjoint.cpp \
    $$PWD/box2dfrictionjoint.cpp \
    $$PWD/box2dwheeljoint.cpp \
    $$PWD/box2dmousejoint.cpp \
    $$PWD/box2dgearjoint.cpp \
    $$PWD/box2dropejoint.cpp



HEADERS += \
    $$PWD/box2dplugin.h \
    $$PWD/box2dworld.h \
    $$PWD/box2dbody.h \
    $$PWD/box2dfixture.h \
    $$PWD/box2ddebugdraw.h \
    $$PWD/box2djoint.h \
    $$PWD/box2drevolutejoint.h \
    $$PWD/box2ddistancejoint.h \
    $$PWD/box2dprismaticjoint.h \
    $$PWD/box2ddestructionlistener.h \
    $$PWD/box2dmotorjoint.h \
    $$PWD/box2dweldjoint.h \
    $$PWD/box2dpulleyjoint.h \
    $$PWD/box2dfrictionjoint.h \
    $$PWD/box2dwheeljoint.h \
    $$PWD/box2dmousejoint.h \
    $$PWD/box2dgearjoint.h \
    $$PWD/box2dropejoint.h

