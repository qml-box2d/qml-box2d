INCLUDEPATH += $$PWD

contains(DEFINES, BOX2D_SYSTEM) {

    packagesExist(box2d) {
        CONFIG += link_pkgconfig
        PKGCONFIG += box2d
    } else {

        !contains(INCLUDEPATH,"Box2D") {
            unix:BOX2D_INCLUDEPATH = "/usr/include/Box2D"
            INCLUDEPATH += $$BOX2D_INCLUDEPATH
        }

        !contains(LIBS,"Box2D")
            LIBS += "-lBox2D"
    }
} else {
    include(Box2D/box2d.pri)
}
