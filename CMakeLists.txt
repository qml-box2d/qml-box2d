cmake_minimum_required (VERSION 3.5.0 FATAL_ERROR)
project (box2dqml)

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

find_package (Qt5 REQUIRED COMPONENTS Quick Core Qml)
add_subdirectory (thirdparty/Box2D)
add_subdirectory (examples)

add_library (${PROJECT_NAME} SHARED
    box2dbody.cpp
    box2dbody.h
    box2dcontact.cpp
    box2dcontact.h
    box2ddebugdraw.cpp
    box2ddebugdraw.h
    box2ddistancejoint.cpp
    box2ddistancejoint.h
    box2dfixture.cpp
    box2dfixture.h
    box2dfrictionjoint.cpp
    box2dfrictionjoint.h
    box2dgearjoint.cpp
    box2dgearjoint.h
    box2djoint.cpp
    box2djoint.h
    box2dmotorjoint.cpp
    box2dmotorjoint.h
    box2dmousejoint.cpp
    box2dmousejoint.h
    box2dplugin.cpp
    box2dplugin.h
    box2dprismaticjoint.cpp
    box2dprismaticjoint.h
    box2dpulleyjoint.cpp
    box2dpulleyjoint.h
    box2draycast.cpp
    box2draycast.h
    box2drevolutejoint.cpp
    box2drevolutejoint.h
    box2dropejoint.cpp
    box2dropejoint.h
    box2dweldjoint.cpp
    box2dweldjoint.h
    box2dwheeljoint.cpp
    box2dwheeljoint.h
    box2dworld.cpp
    box2dworld.h
    qmldir
    )

set_target_properties (${PROJECT_NAME}
PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
)

target_include_directories (${PROJECT_NAME} PUBLIC ./)

target_link_libraries (${PROJECT_NAME}
PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
PUBLIC
    box2d
)
