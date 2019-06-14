cmake_minimum_required (VERSION 3.5.0 FATAL_ERROR)
project (box2dplugin)

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins/Box2D)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins/Box2D)

find_package(Qt5 REQUIRED COMPONENTS Quick Core Qml)

add_library(Box2D SHARED
    
    # Box2D sources
    Box2D/Box2D.h 
    Box2D/Collision/Shapes/b2ChainShape.cpp 
    Box2D/Collision/Shapes/b2ChainShape.h 
    Box2D/Collision/Shapes/b2CircleShape.cpp 
    Box2D/Collision/Shapes/b2CircleShape.h 
    Box2D/Collision/Shapes/b2EdgeShape.cpp 
    Box2D/Collision/Shapes/b2EdgeShape.h 
    Box2D/Collision/Shapes/b2PolygonShape.cpp 
    Box2D/Collision/Shapes/b2PolygonShape.h 
    Box2D/Collision/Shapes/b2Shape.h 
    Box2D/Collision/b2BroadPhase.cpp 
    Box2D/Collision/b2BroadPhase.h 
    Box2D/Collision/b2CollideCircle.cpp 
    Box2D/Collision/b2CollideEdge.cpp 
    Box2D/Collision/b2CollidePolygon.cpp 
    Box2D/Collision/b2Collision.cpp 
    Box2D/Collision/b2Collision.h 
    Box2D/Collision/b2Distance.cpp 
    Box2D/Collision/b2Distance.h 
    Box2D/Collision/b2DynamicTree.cpp 
    Box2D/Collision/b2DynamicTree.h 
    Box2D/Collision/b2TimeOfImpact.cpp 
    Box2D/Collision/b2TimeOfImpact.h 
    Box2D/Common/b2BlockAllocator.cpp 
    Box2D/Common/b2BlockAllocator.h 
    Box2D/Common/b2Draw.cpp 
    Box2D/Common/b2Draw.h 
    Box2D/Common/b2GrowableStack.h 
    Box2D/Common/b2Math.cpp 
    Box2D/Common/b2Math.h 
    Box2D/Common/b2Settings.cpp 
    Box2D/Common/b2Settings.h 
    Box2D/Common/b2StackAllocator.cpp 
    Box2D/Common/b2StackAllocator.h 
    Box2D/Common/b2Timer.cpp 
    Box2D/Common/b2Timer.h 
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp 
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h 
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp 
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h 
    Box2D/Dynamics/Contacts/b2CircleContact.cpp 
    Box2D/Dynamics/Contacts/b2CircleContact.h 
    Box2D/Dynamics/Contacts/b2Contact.cpp 
    Box2D/Dynamics/Contacts/b2Contact.h 
    Box2D/Dynamics/Contacts/b2ContactSolver.cpp 
    Box2D/Dynamics/Contacts/b2ContactSolver.h 
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp 
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h 
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp 
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h 
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp 
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h 
    Box2D/Dynamics/Contacts/b2PolygonContact.cpp 
    Box2D/Dynamics/Contacts/b2PolygonContact.h 
    Box2D/Dynamics/Joints/b2DistanceJoint.cpp 
    Box2D/Dynamics/Joints/b2DistanceJoint.h 
    Box2D/Dynamics/Joints/b2FrictionJoint.cpp 
    Box2D/Dynamics/Joints/b2FrictionJoint.h 
    Box2D/Dynamics/Joints/b2GearJoint.cpp 
    Box2D/Dynamics/Joints/b2GearJoint.h 
    Box2D/Dynamics/Joints/b2Joint.cpp 
    Box2D/Dynamics/Joints/b2Joint.h 
    Box2D/Dynamics/Joints/b2MotorJoint.cpp
    Box2D/Dynamics/Joints/b2MotorJoint.h 
    Box2D/Dynamics/Joints/b2MouseJoint.cpp 
    Box2D/Dynamics/Joints/b2MouseJoint.h 
    Box2D/Dynamics/Joints/b2PrismaticJoint.cpp 
    Box2D/Dynamics/Joints/b2PrismaticJoint.h 
    Box2D/Dynamics/Joints/b2PulleyJoint.cpp 
    Box2D/Dynamics/Joints/b2PulleyJoint.h 
    Box2D/Dynamics/Joints/b2RevoluteJoint.cpp 
    Box2D/Dynamics/Joints/b2RevoluteJoint.h 
    Box2D/Dynamics/Joints/b2RopeJoint.cpp 
    Box2D/Dynamics/Joints/b2RopeJoint.h 
    Box2D/Dynamics/Joints/b2WeldJoint.cpp 
    Box2D/Dynamics/Joints/b2WeldJoint.h 
    Box2D/Dynamics/Joints/b2WheelJoint.cpp 
    Box2D/Dynamics/Joints/b2WheelJoint.h 
    Box2D/Dynamics/b2Body.cpp 
    Box2D/Dynamics/b2Body.h 
    Box2D/Dynamics/b2ContactManager.cpp 
    Box2D/Dynamics/b2ContactManager.h 
    Box2D/Dynamics/b2Fixture.cpp 
    Box2D/Dynamics/b2Fixture.h 
    Box2D/Dynamics/b2Island.cpp 
    Box2D/Dynamics/b2Island.h 
    Box2D/Dynamics/b2TimeStep.h 
    Box2D/Dynamics/b2World.cpp 
    Box2D/Dynamics/b2World.h 
    Box2D/Dynamics/b2WorldCallbacks.cpp 
    Box2D/Dynamics/b2WorldCallbacks.h 
    Box2D/Rope/b2Rope.cpp 
    Box2D/Rope/b2Rope.h 

    # Qml-Box2d
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

set_target_properties (
Box2D
PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
)

target_include_directories(Box2D
PRIVATE
    Box2D
)

target_link_libraries(Box2D
PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
)

add_custom_command(TARGET Box2D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/qmldir
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qmldir
)
