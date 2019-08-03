cmake_minimum_required (VERSION 3.5.0 FATAL_ERROR)
project (box2qml-examples)

find_package (Qt5 REQUIRED COMPONENTS Quick Core Qml)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTORCC ON)

add_executable (${PROJECT_NAME} 
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

    rope/Wall.qml
    rope/main.qml

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

set_target_properties (${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
    )

target_link_libraries (${PROJECT_NAME}
PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
    box2dqml
)
