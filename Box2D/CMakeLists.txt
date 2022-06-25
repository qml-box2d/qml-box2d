#
# Box2D/CMakeLists.txt
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

add_library (Box2D STATIC
    Box2D.h
    Collision/Shapes/b2ChainShape.cpp
    Collision/Shapes/b2ChainShape.h
    Collision/Shapes/b2CircleShape.cpp
    Collision/Shapes/b2CircleShape.h
    Collision/Shapes/b2EdgeShape.cpp
    Collision/Shapes/b2EdgeShape.h
    Collision/Shapes/b2PolygonShape.cpp
    Collision/Shapes/b2PolygonShape.h
    Collision/Shapes/b2Shape.h
    Collision/b2BroadPhase.cpp
    Collision/b2BroadPhase.h
    Collision/b2CollideCircle.cpp
    Collision/b2CollideEdge.cpp
    Collision/b2CollidePolygon.cpp
    Collision/b2Collision.cpp
    Collision/b2Collision.h
    Collision/b2Distance.cpp
    Collision/b2Distance.h
    Collision/b2DynamicTree.cpp
    Collision/b2DynamicTree.h
    Collision/b2TimeOfImpact.cpp
    Collision/b2TimeOfImpact.h
    Common/b2BlockAllocator.cpp
    Common/b2BlockAllocator.h
    Common/b2Draw.cpp
    Common/b2Draw.h
    Common/b2GrowableStack.h
    Common/b2Math.cpp
    Common/b2Math.h
    Common/b2Settings.cpp
    Common/b2Settings.h
    Common/b2StackAllocator.cpp
    Common/b2StackAllocator.h
    Common/b2Timer.cpp
    Common/b2Timer.h
    Dynamics/Contacts/b2ChainAndCircleContact.cpp
    Dynamics/Contacts/b2ChainAndCircleContact.h
    Dynamics/Contacts/b2ChainAndPolygonContact.cpp
    Dynamics/Contacts/b2ChainAndPolygonContact.h
    Dynamics/Contacts/b2CircleContact.cpp
    Dynamics/Contacts/b2CircleContact.h
    Dynamics/Contacts/b2Contact.cpp
    Dynamics/Contacts/b2Contact.h
    Dynamics/Contacts/b2ContactSolver.cpp
    Dynamics/Contacts/b2ContactSolver.h
    Dynamics/Contacts/b2EdgeAndCircleContact.cpp
    Dynamics/Contacts/b2EdgeAndCircleContact.h
    Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
    Dynamics/Contacts/b2EdgeAndPolygonContact.h
    Dynamics/Contacts/b2PolygonAndCircleContact.cpp
    Dynamics/Contacts/b2PolygonAndCircleContact.h
    Dynamics/Contacts/b2PolygonContact.cpp
    Dynamics/Contacts/b2PolygonContact.h
    Dynamics/Joints/b2DistanceJoint.cpp
    Dynamics/Joints/b2DistanceJoint.h
    Dynamics/Joints/b2FrictionJoint.cpp
    Dynamics/Joints/b2FrictionJoint.h
    Dynamics/Joints/b2GearJoint.cpp
    Dynamics/Joints/b2GearJoint.h
    Dynamics/Joints/b2Joint.cpp
    Dynamics/Joints/b2Joint.h
    Dynamics/Joints/b2MotorJoint.cpp
    Dynamics/Joints/b2MotorJoint.h
    Dynamics/Joints/b2MouseJoint.cpp
    Dynamics/Joints/b2MouseJoint.h
    Dynamics/Joints/b2PrismaticJoint.cpp
    Dynamics/Joints/b2PrismaticJoint.h
    Dynamics/Joints/b2PulleyJoint.cpp
    Dynamics/Joints/b2PulleyJoint.h
    Dynamics/Joints/b2RevoluteJoint.cpp
    Dynamics/Joints/b2RevoluteJoint.h
    Dynamics/Joints/b2RopeJoint.cpp
    Dynamics/Joints/b2RopeJoint.h
    Dynamics/Joints/b2WeldJoint.cpp
    Dynamics/Joints/b2WeldJoint.h
    Dynamics/Joints/b2WheelJoint.cpp
    Dynamics/Joints/b2WheelJoint.h
    Dynamics/b2Body.cpp
    Dynamics/b2Body.h
    Dynamics/b2ContactManager.cpp
    Dynamics/b2ContactManager.h
    Dynamics/b2Fixture.cpp
    Dynamics/b2Fixture.h
    Dynamics/b2Island.cpp
    Dynamics/b2Island.h
    Dynamics/b2TimeStep.h
    Dynamics/b2World.cpp
    Dynamics/b2World.h
    Dynamics/b2WorldCallbacks.cpp
    Dynamics/b2WorldCallbacks.h
    Rope/b2Rope.cpp
    Rope/b2Rope.h
    )

add_library (box2d::box2d ALIAS Box2D)

set_target_properties (Box2D
PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE ON
)

target_include_directories (Box2D PUBLIC .. ${CMAKE_CURRENT_SOURCE_DIR})
