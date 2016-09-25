include(../box2d_lib.pri)


ios{
    CXX_MODULE=qml
    QMAKE_MOC_OPTIONS += -Muri=Box2D
}


TEMPLATE = lib
CONFIG += plugin CONFIG += warning_clean
QT += qml quick
TARGET = $$qtLibraryTarget(Box2D)
TARGETPATH = Box2D
uri=Box2D
API_VER=2.0


## Why ? Is this for win32 only ?
#MOC_DIR = .moc
#OBJECTS_DIR = .obj

contains(QT_CONFIG, reduce_exports): CONFIG += hide_symbols

# Uncomment the line below to compile qml-box2d plugin with Box2D library, installed in OS
# or pass the variable to qmake in command line:
# qmake DEFINES+=BOX2D_SYSTEM
# Warning: Box2D library must be already installed in system, for example in Debian it could be done with:
# sudo apt-get install libbox2d-dev

#DEFINES += BOX2D_SYSTEM



SOURCES += \
    $$PWD/box2dbody.cpp \
    $$PWD/box2dcontact.cpp \
    $$PWD/box2ddebugdraw.cpp \
    $$PWD/box2ddistancejoint.cpp \
    $$PWD/box2dfixture.cpp \
    $$PWD/box2dfrictionjoint.cpp \
    $$PWD/box2dgearjoint.cpp \
    $$PWD/box2djoint.cpp \
    $$PWD/box2dmotorjoint.cpp \
    $$PWD/box2dmousejoint.cpp \
    $$PWD/box2dplugin.cpp \
    $$PWD/box2dprismaticjoint.cpp \
    $$PWD/box2dpulleyjoint.cpp \
    $$PWD/box2draycast.cpp \
    $$PWD/box2drevolutejoint.cpp \
    $$PWD/box2dropejoint.cpp \
    $$PWD/box2dweldjoint.cpp \
    $$PWD/box2dwheeljoint.cpp \
    $$PWD/box2dworld.cpp


HEADERS += \
    $$PWD/box2dbody.h \
    $$PWD/box2dcontact.h \
    $$PWD/box2ddebugdraw.h \
    $$PWD/box2ddistancejoint.h \
    $$PWD/box2dfixture.h \
    $$PWD/box2dfrictionjoint.h \
    $$PWD/box2dgearjoint.h \
    $$PWD/box2djoint.h \
    $$PWD/box2dmotorjoint.h \
    $$PWD/box2dmousejoint.h \
    $$PWD/box2dplugin.h \
    $$PWD/box2dprismaticjoint.h \
    $$PWD/box2dpulleyjoint.h \
    $$PWD/box2draycast.h \
    $$PWD/box2drevolutejoint.h \
    $$PWD/box2dropejoint.h \
    $$PWD/box2dweldjoint.h \
    $$PWD/box2dwheeljoint.h \
    $$PWD/box2dworld.h



qmldir.files += $$PWD/qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}


# FIXME generate .qmltype files here


qmltypes.files = $$PWD/plugins.qmltypes
qmltypes.target = qmltypes
qmltypes.commands = $$[QT_INSTALL_BINS]/qmlplugindump $$uri 2.0 $$QMAKE_RESOLVED_TARGET > $$PWD/plugins.qmltypes
qmltypes.depends = $$QMAKE_RESOLVED_TARGET
QMAKE_EXTRA_TARGETS += qmltypes





## QUESTION why append the version number ?
## importPath = $$[QT_INSTALL_QML]/$$replace(TARGETPATH, \\., /).$$API_VER

installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
target.path = $$installPath


qmltypes.path = $$installPath
qmldir.path = $$installPath

INSTALLS += target qmldir qmltypes
