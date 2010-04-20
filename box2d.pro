TEMPLATE = lib
CONFIG += plugin
QT += declarative
TARGET = Box2D
DESTDIR = ../../lib/Box2D
include(Box2D/box2d.pri)
MOC_DIR = .moc
OBJECTS_DIR = .obj

SOURCES += box2dplugin.cpp \
    box2dworld.cpp \
    box2dbody.cpp

HEADERS += \
    box2dplugin.h \
    box2dworld.h \
    box2dbody.h

# Copy over the qmldir file
QMLDIR = $${_PRO_FILE_PWD_}/qmldir
QMAKE_POST_LINK += $${QMAKE_COPY} $${QMLDIR} $${DESTDIR}
