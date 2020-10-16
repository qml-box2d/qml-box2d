#
# plugin/CMakeLists.txt
# Copyright (c) 2019 Serein Pfeiffer <serein.pfeiffer@gmail.com>
#
# This file is part of the Box2D QML plugin.
#
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from
# the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software in
#    a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#
cmake_minimum_required (VERSION 3.5.0 FATAL_ERROR)
project (box2dqml)

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

find_package (Qt5 REQUIRED COMPONENTS Quick Core Qml)

if (NOT QML_PLUGIN_LINK_TYPE)
  set(QML_PLUGIN_LINK_TYPE SHARED)
endif()

add_library (${PROJECT_NAME} ${QML_PLUGIN_LINK_TYPE}
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

set (PLUGIN_DEST_DIR "${QMLBOX2D_PLUGIN_BASE_DIR}/Box2D")
set_target_properties(
${PROJECT_NAME}
PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
    LIBRARY_OUTPUT_DIRECTORY "${PLUGIN_DEST_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PLUGIN_DEST_DIR}"
)

target_include_directories (${PROJECT_NAME} PUBLIC ./)

target_compile_definitions(${PROJECT_NAME}
PRIVATE
    $<$<STREQUAL:${QML_PLUGIN_LINK_TYPE},STATIC>:QT_STATICPLUGIN>
)

target_link_libraries (${PROJECT_NAME}
PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
PUBLIC
    box2d
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/qmldir
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/qmldir
)
