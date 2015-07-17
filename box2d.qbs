import qbs

Project {
    name: "box2d";

    DynamicLibrary {
        name: "box2d"
        files: []
        Depends { name: "cpp" }
        Group   { name: "Headers";    files: ["Box2D/*.h", "Box2D/*/*.h", "Box2D/*/*/*.h"]; }
        Group   { name: "Sources";    files: ["Box2D/*.cpp", "Box2D/*/*.cpp", "Box2D/*/*/*.cpp"]; }
        cpp.includePaths: ["Box2D", "."]

        Group { qbs.install: true; fileTagsFilter: product.type;}
    }

    DynamicLibrary {
        name: "box2d_lib"
        files: []
        Depends { name: "cpp" }
        Depends { name: "box2d" }
        Depends { name: "Qt"; submodules: ["core", "qml", "quick"]; }
        Group   { name: "Headers";    files: ["*.h"]; }
        Group   { name: "Sources";    files: ["*.cpp"]; }
        cpp.includePaths: ["Box2D", "."]

        Group { qbs.install: true; fileTagsFilter: product.type;}
    }
}

