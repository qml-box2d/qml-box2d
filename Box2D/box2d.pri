# Box2D sources
INCLUDEPATH += $$PWD/Include
SOURCES = \
	$$PWD/Source/Dynamics/b2Body.cpp \
	$$PWD/Source/Dynamics/b2Island.cpp \
	$$PWD/Source/Dynamics/b2World.cpp \
	$$PWD/Source/Dynamics/b2ContactManager.cpp \
	$$PWD/Source/Dynamics/Contacts/b2Contact.cpp \
	$$PWD/Source/Dynamics/Contacts/b2PolyContact.cpp \
	$$PWD/Source/Dynamics/Contacts/b2CircleContact.cpp \
	$$PWD/Source/Dynamics/Contacts/b2PolyAndCircleContact.cpp \
	$$PWD/Source/Dynamics/Contacts/b2ContactSolver.cpp \
	$$PWD/Source/Dynamics/b2WorldCallbacks.cpp \
	$$PWD/Source/Dynamics/Joints/b2MouseJoint.cpp \
	$$PWD/Source/Dynamics/Joints/b2PulleyJoint.cpp \
	$$PWD/Source/Dynamics/Joints/b2Joint.cpp \
	$$PWD/Source/Dynamics/Joints/b2RevoluteJoint.cpp \
	$$PWD/Source/Dynamics/Joints/b2PrismaticJoint.cpp \
	$$PWD/Source/Dynamics/Joints/b2DistanceJoint.cpp \
	$$PWD/Source/Dynamics/Joints/b2GearJoint.cpp \
	$$PWD/Source/Common/b2StackAllocator.cpp \
	$$PWD/Source/Common/b2Math.cpp \
	$$PWD/Source/Common/b2BlockAllocator.cpp \
	$$PWD/Source/Common/b2Settings.cpp \
	$$PWD/Source/Collision/b2Collision.cpp \
	$$PWD/Source/Collision/b2Distance.cpp \
	$$PWD/Source/Collision/Shapes/b2Shape.cpp \
	$$PWD/Source/Collision/Shapes/b2CircleShape.cpp \
	$$PWD/Source/Collision/Shapes/b2PolygonShape.cpp \
	$$PWD/Source/Collision/b2TimeOfImpact.cpp \
	$$PWD/Source/Collision/b2PairManager.cpp \
	$$PWD/Source/Collision/b2CollidePoly.cpp \
	$$PWD/Source/Collision/b2CollideCircle.cpp \
	$$PWD/Source/Collision/b2BroadPhase.cpp 
HEADERS = \
	$$PWD/Source/Dynamics/b2Body.h \
	$$PWD/Source/Dynamics/b2Island.h \
	$$PWD/Source/Dynamics/b2World.h \
	$$PWD/Source/Dynamics/b2ContactManager.h \
	$$PWD/Source/Dynamics/Contacts/b2Contact.h \
	$$PWD/Source/Dynamics/Contacts/b2PolyContact.h \
	$$PWD/Source/Dynamics/Contacts/b2CircleContact.h \
	$$PWD/Source/Dynamics/Contacts/b2PolyAndCircleContact.h \
	$$PWD/Source/Dynamics/Contacts/b2ContactSolver.h \
	$$PWD/Source/Dynamics/b2WorldCallbacks.h \
	$$PWD/Source/Dynamics/Joints/b2MouseJoint.h \
	$$PWD/Source/Dynamics/Joints/b2PulleyJoint.h \
	$$PWD/Source/Dynamics/Joints/b2Joint.h \
	$$PWD/Source/Dynamics/Joints/b2RevoluteJoint.h \
	$$PWD/Source/Dynamics/Joints/b2PrismaticJoint.h \
	$$PWD/Source/Dynamics/Joints/b2DistanceJoint.h \
	$$PWD/Source/Dynamics/Joints/b2GearJoint.h \
	$$PWD/Source/Common/b2StackAllocator.h \
	$$PWD/Source/Common/b2Math.h \
	$$PWD/Source/Common/b2BlockAllocator.h \
	$$PWD/Source/Common/b2Settings.h \
	$$PWD/Source/Common/Fixed.h \
	$$PWD/Source/Common/jtypes.h \
	$$PWD/Source/Collision/b2Collision.h \
	$$PWD/Source/Collision/Shapes/b2Shape.h \
	$$PWD/Source/Collision/Shapes/b2CircleShape.h \
	$$PWD/Source/Collision/Shapes/b2PolygonShape.h \
	$$PWD/Source/Collision/b2PairManager.h \
	$$PWD/Source/Collision/b2BroadPhase.h
