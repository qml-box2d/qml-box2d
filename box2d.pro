include(docs/docs.pri)

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
        $$PWD/src/box2d.pro \
        $$PWD/src/Components \
        $$PWD/examples/examples.pro

OTHER_FILES += \
        $$PWD/box2d_lib.pri \
        $$PWD/box2d.qbs \
        $$PWD/box2d-static.pri \
        $$PWD/COPYING \
        $$PWD/README.md \
        $$PWD/debian/changelog \
        $$PWD/debian/compat \
        $$PWD/debian/control \
        $$PWD/debian/rules
