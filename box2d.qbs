import qbs

Project {
    name: "box2d";

    StaticLibrary {
        name: "box2d"
        files: ["Box2D/*.h", "Box2D/*/*.h", "Box2D/*/*/*.h", "Box2D/*.cpp", "Box2D/*/*.cpp", "Box2D/*/*/*.cpp"]
        Depends { name: "cpp" }
        cpp.includePaths: ["Box2D", "."]

        Group { qbs.install: true; fileTagsFilter: product.type;}
    }

    DynamicLibrary {
        name: "box2d_lib"
        files: ["*.h", "*.cpp"]
        Depends { name: "cpp" }
        Depends { name: "box2d" }
        Depends { name: "Qt"; submodules: ["core", "qml", "quick"]; }
        cpp.includePaths: ["Box2D", "."]

        Group { qbs.install: true; fileTagsFilter: product.type;}

        Export {
            Depends { name: "cpp" }
            cpp.includePaths: "."
        }
    }
}

