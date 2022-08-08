#
# CMakeLists.txt
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
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(qmlbox2d)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(QMLBOX2D_PLUGIN_BASE_DIR ${CMAKE_BINARY_DIR}/bin/plugins)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QML_BOX2D_LIBRARY_NAME "${PROJECT_NAME}")

include(CheckIPOSupported)
check_ipo_supported(RESULT ipoSupported)

option(USE_QT6 "Use Qt6 by default, else use Qt5" ON)
option(USE_SYSTEM_BOX2D "Use system box2d if compatible" OFF)
option(BUILD_EXAMPLES "Build the examples" ON)
option(BUILD_SHARED_LIBS "Build qml-box2d as a shared lib" ON)

set(QT_MAJOR_VERSION Qt6)

if(USE_QT6)
  find_package(Qt6 6.2 COMPONENTS Quick Core Qml)
endif()

if(NOT Qt6_FOUND)
    find_package(Qt5 5.12 COMPONENTS Quick Core Qml REQUIRED)
    set(QT_MAJOR_VERSION Qt5)
endif()

message(STATUS "Using ${QT_MAJOR_VERSION}")

if(BUILD_SHARED_LIBS)
  set(QML_PLUGIN_LINK_TYPE SHARED)
else()
  set(QML_PLUGIN_LINK_TYPE STATIC)
endif()

set(QML_BOX2D_SOURCES
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
    box2dweldjoint.cpp
    box2dweldjoint.h
    box2dwheeljoint.cpp
    box2dwheeljoint.h
    box2dworld.cpp
    box2dworld.h
    qmldir
)

add_library(${QML_BOX2D_LIBRARY_NAME} ${QML_PLUGIN_LINK_TYPE}
  ${QML_BOX2D_SOURCES}
)

if(ipoSupported)
  set_property(TARGET ${QML_BOX2D_LIBRARY_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set_target_properties(${QML_BOX2D_LIBRARY_NAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)

set(PLUGIN_DEST_DIR "${QMLBOX2D_PLUGIN_BASE_DIR}/Box2D")
set_target_properties(
${QML_BOX2D_LIBRARY_NAME}
PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
    ARCHIVE_OUTPUT_DIRECTORY "${PLUGIN_DEST_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${PLUGIN_DEST_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PLUGIN_DEST_DIR}"
)

target_include_directories(${QML_BOX2D_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${QML_BOX2D_LIBRARY_NAME}
PRIVATE
    $<$<STREQUAL:${QML_PLUGIN_LINK_TYPE},STATIC>:QT_STATICPLUGIN>
)

if(MINGW)
  # Remove lib prefix when compiling with mingw on Windows to have the same library name as in qmldir
  set_target_properties(${QML_BOX2D_LIBRARY_NAME} PROPERTIES PREFIX "")
endif()

target_link_libraries(${QML_BOX2D_LIBRARY_NAME}
PRIVATE
    ${QT_MAJOR_VERSION}::Core
    ${QT_MAJOR_VERSION}::Quick
    ${QT_MAJOR_VERSION}::Qml
)

if(NOT Qt6_FOUND)
  add_custom_command(TARGET ${QML_BOX2D_LIBRARY_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/qmldir
    $<TARGET_FILE_DIR:${QML_BOX2D_LIBRARY_NAME}>/qmldir
  )
endif()

if(Qt6_FOUND)
    set_target_properties(${QML_BOX2D_LIBRARY_NAME} PROPERTIES
        QT_QML_MODULE_VERSION 2.0
        QT_QML_MODULE_URI     Box2D
    )
    qt_add_qml_module(${QML_BOX2D_LIBRARY_NAME}
      URI Box2D
      VERSION 2.0
      PLUGIN_TARGET ${QML_BOX2D_LIBRARY_NAME}
      OUTPUT_DIRECTORY "${PLUGIN_DEST_DIR}"
      NO_GENERATE_PLUGIN_SOURCE
    )
endif()

if(USE_SYSTEM_BOX2D)
  find_package(box2d REQUIRED)
  if(NOT TARGET box2d::box2d)
    message(FATAL_ERROR "System box2d not found")
  endif()
  target_link_libraries(${QML_BOX2D_LIBRARY_NAME} PUBLIC box2d::box2d)
endif()

if(NOT USE_SYSTEM_BOX2D)
  # make sure submodule is up2date
  find_package(Git)
  if(GIT_FOUND)
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  endif()

  include(ExternalProject)
  ExternalProject_Add(box2d-external
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/box2d
    CMAKE_ARGS -DBOX2D_BUILD_UNIT_TESTS=OFF;-DBOX2D_BUILD_TESTBED=OFF;-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    BUILD_ALWAYS ON
  )
  target_include_directories(${QML_BOX2D_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/box2d/include)
  ExternalProject_Get_property(box2d-external INSTALL_DIR)
  add_library(box2d-local STATIC IMPORTED)
  set_target_properties(box2d-local PROPERTIES IMPORTED_LOCATION ${INSTALL_DIR}/lib/libbox2d.a)
  target_link_libraries(${QML_BOX2D_LIBRARY_NAME} PUBLIC box2d-local)
  add_dependencies(${QML_BOX2D_LIBRARY_NAME} box2d-external)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

include(GNUInstallDirs)

install(
  TARGETS qmlbox2d
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/Box2D"
)
install(
  FILES qmldir
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/Box2D"
)
