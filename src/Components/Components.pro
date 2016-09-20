TEMPLATE = lib
QT += qml quick
TARGET = Box2D.Components
uri=Box2D.Components
CONFIG += plugin

##FIXME there needs to be a dummy class for ios to work
ios{
    CXX_MODULE=qml
    QMAKE_MOC_OPTIONS += -Muri=Box2D.Component
}



qmlFiles.files += \
        $$PWD/BoxBody.qml \
        $$PWD/ChainBody.qml \
        $$PWD/CircleBody.qml \
        $$PWD/EdgeBody.qml \
        $$PWD/ImageBoxBody.qml \
        $$PWD/PhysicsItem.qml \
        $$PWD/PolygonBody.qml \
        $$PWD/RectangleBoxBody.qml \
        $$PWD/ScreenBoundaries.qml

qmldir.files = qmldir


## To view in the qtcreator
OTHER_FILES += += \
        $$PWD/BoxBody.qml \
        $$PWD/ChainBody.qml \
        $$PWD/CircleBody.qml \
        $$PWD/EdgeBody.qml \
        $$PWD/ImageBoxBody.qml \
        $$PWD/PhysicsItem.qml \
        $$PWD/PolygonBody.qml \
        $$PWD/RectangleBoxBody.qml \
        $$PWD/ScreenBoundaries.qml \
        $$PWD/qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}



# FIXME generate .qmltype files here
# plugin.qmltypes is used by Qt Creator for syntax highlighting and the QML code model.  It needs
# to be regenerated whenever the QML elements exported by the plugin change.  This cannot be done
# automatically at compile time because qmlplugindump does not support some QML features and it may
# not be possible when cross-compiling.
#
# To regenerate run 'make qmltypes' which will update the plugins.qmltypes file in the source
# directory.  Then review and commit the changes made to plugins.qmltypes.
#
qmltypes.files = $$PWD/plugins.qmltypes
qmltypes.target = qmltypes
qmltypes.commands = $$[QT_INSTALL_BINS]/qmlplugindump $$uri 1.0 $$QMAKE_RESOLVED_TARGET > $$PWD/plugins.qmltypes
qmltypes.depends = $$QMAKE_RESOLVED_TARGET
QMAKE_EXTRA_TARGETS += qmltypes



installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

qmldir.path = $$installPath
qmltypes.path = $$installPath

qmlFiles.path = $$installPath
target.path = $$installPath

INSTALLS += qmlFiles qmldir qmltypes
