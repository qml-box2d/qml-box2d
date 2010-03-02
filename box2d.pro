TEMPLATE = lib
QT += declarative
TARGET = Box2D
DESTDIR = ../../lib/Box2D
include(Box2D/box2d.pri)
MOC_DIR = .moc
OBJECTS_DIR = .obj

SOURCES += box2dplugin.cpp \
    box2dworld.cpp

HEADERS += \
    box2dplugin.h \
    box2dworld.h
