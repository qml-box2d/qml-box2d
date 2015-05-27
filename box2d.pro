TEMPLATE = lib
CONFIG += plugin
QT += quick
TARGET = $$qtLibraryTarget(Box2D)
TARGETPATH = Box2D
API_VER=2.0
MOC_DIR = .moc
OBJECTS_DIR = .obj

contains(QT_CONFIG, reduce_exports): CONFIG += hide_symbols

# Uncomment the line below to compile qml-box2d plugin with Box2D library, installed in OS
# or pass the variable to qmake in command line:
# qmake DEFINES+=BOX2D_SYSTEM
# Warning: Box2D library must be already installed in system, for example in Debian it could be done with:
# sudo apt-get install libbox2d-dev

#DEFINES += BOX2D_SYSTEM

include(box2d_lib.pri)
include(examples/examples.pri)

importPath = $$[QT_INSTALL_QML]/$$replace(TARGETPATH, \\., /).$$API_VER
target.path = $${importPath}

qmldir.path = $${importPath}
qmldir.files += $$PWD/qmldir


INSTALLS += target qmldir


