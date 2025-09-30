#
# examples/CMakeLists.txt
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
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)

if(Qt6_FOUND)
  find_package(Qt6 6.2 COMPONENTS Widgets REQUIRED)
else()
  find_package(Qt5 5.12 COMPONENTS Widgets REQUIRED)
endif()

add_executable(box2qml-examples
    main.cpp
    example.qrc

    accelerometer/WoodenBox.qml
    accelerometer/accelerometer.qml

    angletracking/Line.qml
    angletracking/angleTracking.qml

    boxes/Wall.qml
    boxes/WoodenBox.qml
    boxes/boxes.qml

    cannon/Wall.qml
    cannon/main.qml

    contacts/Wall.qml
    contacts/main.qml

    demolition/Building.qml
    demolition/Wall.qml
    demolition/WoodenBox.qml
    demolition/demolition.qml

    distance/Ball.qml
    distance/Square.qml
    distance/distance.qml

    filtering/filtering.qml

    fixtures/Wall.qml
    fixtures/main.qml

    friction/Wall.qml
    friction/main.qml

    gear/Wall.qml
    gear/main.qml

    impulse/Ball.qml
    impulse/impulse.qml

    monera/SpeciesInfo.qml
    monera/SpeciesModel.qml
    monera/monera.qml

    motorjoint/boat.qml

    mouse/Wall.qml
    mouse/main.qml

    movingBox/MovableBox.qml
    movingBox/Wall.qml
    movingBox/WoodenBox.qml
    movingBox/movingBox.qml

    polygons/Trapezoid.qml
    polygons/polygons.qml
    
    prismatic/Square.qml
    prismatic/prismatic.qml

    pulley/Wall.qml
    pulley/main.qml

    raycast/Wall.qml
    raycast/main.qml

    revolute/revolute.qml

    revoluteplotangle/Revolute.qml
    revoluteplotangle/revolutePlotAngle.qml

    shared/BoxBody.qml
    shared/ChainBody.qml
    shared/CircleBody.qml
    shared/EdgeBody.qml
    shared/ImageBoxBody.qml
    shared/PhysicsItem.qml
    shared/PolygonBody.qml
    shared/RectangleBoxBody.qml
    shared/ScreenBoundaries.qml

    ui.qml

    weld/Wall.qml
    weld/main.qml

    wheel/Wall.qml
    wheel/main.qml
)

set_target_properties(box2qml-examples PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
    )

target_include_directories(box2qml-examples PUBLIC ..)

target_link_libraries(box2qml-examples
PRIVATE
    ${QT_MAJOR_VERSION}::Core
    ${QT_MAJOR_VERSION}::Quick
    ${QT_MAJOR_VERSION}::Widgets
    ${QT_MAJOR_VERSION}::Qml
PUBLIC
    qmlbox2d
)
