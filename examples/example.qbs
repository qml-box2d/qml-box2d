import qbs
import "../box2d.qbs" as Box2D

Project {
    name: "Example";

    Box2D { }

    Product {
        files: ["main.cpp"];
        name: "Example";
        type: "application";

        Depends { name: "cpp"; }
        Depends { name: "Qt"; submodules: ["core", "qml", "quick"]; }
        Depends { name: "box2d_lib"; }
        Group   { name: "QML Files";    files: ["*.qml", "*/*.qml"]; }
        Group   { name: "QRC Files";    files: ["*.qrc"] }
        Group   { name: "Script Files"; files: ["*.js", "*/*.js"] }

        cpp.includePaths: [".."]

        Group { qbs.install: true; fileTagsFilter: product.type;}

    }
}

