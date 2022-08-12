import qbs

Project {
    name: "box2d";

    StaticLibrary {
        name: "box2d"
        files: ["external/box2d/include/box2d/*.h", "external/box2d/src/*/*.cpp"]
        Depends { name: "cpp" }
        cpp.includePaths: ["external/box2d/include", "external/box2d/src"]

        Group { qbs.install: true; fileTagsFilter: product.type;}
    }

    DynamicLibrary {
        name: "box2d_lib"
        files: ["*.h", "*.cpp"]
        Depends { name: "cpp" }
        Depends { name: "box2d" }
        Depends { name: "Qt"; submodules: ["core", "qml", "quick"]; }
        cpp.includePaths: ["external/box2d/include", "."]

        Group { qbs.install: true; fileTagsFilter: product.type;}

        Export {
            Depends { name: "cpp" }
            cpp.includePaths: "."
        }
    }
}

