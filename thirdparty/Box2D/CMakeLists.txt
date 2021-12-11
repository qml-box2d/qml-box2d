#
# thirdparty/Box2D/CMakeLists.txt
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
project (box2dcpp)

set(box2d_sources
    src/Box2D/Box2D.h
    src/Box2D/Collision/Shapes/b2ChainShape.cpp
    src/Box2D/Collision/Shapes/b2ChainShape.h
    src/Box2D/Collision/Shapes/b2CircleShape.cpp
    src/Box2D/Collision/Shapes/b2CircleShape.h
    src/Box2D/Collision/Shapes/b2EdgeShape.cpp
    src/Box2D/Collision/Shapes/b2EdgeShape.h
    src/Box2D/Collision/Shapes/b2PolygonShape.cpp
    src/Box2D/Collision/Shapes/b2PolygonShape.h
    src/Box2D/Collision/Shapes/b2Shape.h
    src/Box2D/Collision/b2BroadPhase.cpp
    src/Box2D/Collision/b2BroadPhase.h
    src/Box2D/Collision/b2CollideCircle.cpp
    src/Box2D/Collision/b2CollideEdge.cpp
    src/Box2D/Collision/b2CollidePolygon.cpp
    src/Box2D/Collision/b2Collision.cpp
    src/Box2D/Collision/b2Collision.h
    src/Box2D/Collision/b2Distance.cpp
    src/Box2D/Collision/b2Distance.h
    src/Box2D/Collision/b2DynamicTree.cpp
    src/Box2D/Collision/b2DynamicTree.h
    src/Box2D/Collision/b2TimeOfImpact.cpp
    src/Box2D/Collision/b2TimeOfImpact.h
    src/Box2D/Common/b2BlockAllocator.cpp
    src/Box2D/Common/b2BlockAllocator.h
    src/Box2D/Common/b2Draw.cpp
    src/Box2D/Common/b2Draw.h
    src/Box2D/Common/b2GrowableStack.h
    src/Box2D/Common/b2Math.cpp
    src/Box2D/Common/b2Math.h
    src/Box2D/Common/b2Settings.cpp
    src/Box2D/Common/b2Settings.h
    src/Box2D/Common/b2StackAllocator.cpp
    src/Box2D/Common/b2StackAllocator.h
    src/Box2D/Common/b2Timer.cpp
    src/Box2D/Common/b2Timer.h
    src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
    src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h
    src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
    src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h
    src/Box2D/Dynamics/Contacts/b2CircleContact.cpp
    src/Box2D/Dynamics/Contacts/b2CircleContact.h
    src/Box2D/Dynamics/Contacts/b2Contact.cpp
    src/Box2D/Dynamics/Contacts/b2Contact.h
    src/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
    src/Box2D/Dynamics/Contacts/b2ContactSolver.h
    src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
    src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h
    src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
    src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h
    src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
    src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h
    src/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
    src/Box2D/Dynamics/Contacts/b2PolygonContact.h
    src/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
    src/Box2D/Dynamics/Joints/b2DistanceJoint.h
    src/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
    src/Box2D/Dynamics/Joints/b2FrictionJoint.h
    src/Box2D/Dynamics/Joints/b2GearJoint.cpp
    src/Box2D/Dynamics/Joints/b2GearJoint.h
    src/Box2D/Dynamics/Joints/b2Joint.cpp
    src/Box2D/Dynamics/Joints/b2Joint.h
    src/Box2D/Dynamics/Joints/b2MotorJoint.cpp
    src/Box2D/Dynamics/Joints/b2MotorJoint.h
    src/Box2D/Dynamics/Joints/b2MouseJoint.cpp
    src/Box2D/Dynamics/Joints/b2MouseJoint.h
    src/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
    src/Box2D/Dynamics/Joints/b2PrismaticJoint.h
    src/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
    src/Box2D/Dynamics/Joints/b2PulleyJoint.h
    src/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
    src/Box2D/Dynamics/Joints/b2RevoluteJoint.h
    src/Box2D/Dynamics/Joints/b2RopeJoint.cpp
    src/Box2D/Dynamics/Joints/b2RopeJoint.h
    src/Box2D/Dynamics/Joints/b2WeldJoint.cpp
    src/Box2D/Dynamics/Joints/b2WeldJoint.h
    src/Box2D/Dynamics/Joints/b2WheelJoint.cpp
    src/Box2D/Dynamics/Joints/b2WheelJoint.h
    src/Box2D/Dynamics/b2Body.cpp
    src/Box2D/Dynamics/b2Body.h
    src/Box2D/Dynamics/b2ContactManager.cpp
    src/Box2D/Dynamics/b2ContactManager.h
    src/Box2D/Dynamics/b2Fixture.cpp
    src/Box2D/Dynamics/b2Fixture.h
    src/Box2D/Dynamics/b2Island.cpp
    src/Box2D/Dynamics/b2Island.h
    src/Box2D/Dynamics/b2TimeStep.h
    src/Box2D/Dynamics/b2World.cpp
    src/Box2D/Dynamics/b2World.h
    src/Box2D/Dynamics/b2WorldCallbacks.cpp
    src/Box2D/Dynamics/b2WorldCallbacks.h
    src/Box2D/Rope/b2Rope.cpp
    src/Box2D/Rope/b2Rope.h
    )

if (ANDROID)
    add_library (${PROJECT_NAME} OBJECT ${box2d_sources})
else()
    add_library (${PROJECT_NAME} STATIC ${box2d_sources})
endif()


set_target_properties (${PROJECT_NAME}
PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE ON
)

if (ANDROID)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_NAME "${PROJECT_NAME}_${ANDROID_ABI}"
        )
endif()
target_include_directories (${PROJECT_NAME}
PUBLIC
    src
)
