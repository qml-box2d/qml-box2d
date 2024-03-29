import qbs
import "../box2d.qbs" as Box2D

Project {
    name: "Example";

    Box2D { }

    Application {
        files: ["main.cpp", "*.qml", "*/*.qml", "*.qrc", "*.js", "*/*.js"];
        name: "Example";

        Depends { name: "cpp"; }
        Depends { name: "Qt"; submodules: ["core", "qml", "quick", "widgets"]; }
        Depends { name: "box2d_lib"; }

        cpp.rpaths: ["$ORIGIN"]

        Group { qbs.install: true; fileTagsFilter: product.type; }
    }
}

