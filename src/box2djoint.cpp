/*
 * box2djoint.cpp
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 *
 * This file is part of the Box2D QML plugin.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "box2djoint.h"
#include "box2dworld.h"
#include "box2dbody.h"

#include <QDebug>
/*!
   \qmltype Joint
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
    \brief A Joint is a uncreatalbe elemnt that is used in Other Joints such as a PulleyJoint


   Here is a table of all the Joints that inhert Joint
    \table
        \header
        \li Element \li description
            \row
                \li \l {Joint}{Joints}
                \li The overall picture of what Joints are. This is a uncreatable element
            \row
                \li \l {DistanceJoint}{DistanceJoint}
                \li like a box but a polygon
            \row
                \li \l {PrismaticJoint}{PrismaticJoint}
                \li like a box but a polygon
            \row
                \li \l {RevoluteJoint}{RevoluteJoint}
                \li like a box but a polygon
            \row
                \li \l {MotorJoint}{MotorJoint}
                \li like a box but a polygon
            \row
                \li \l {WeldJoint}{WeldJoint}
                \li like a box but a polygon
            \row
                \li \l {PulleyJoint}{PulleyJoint}
                \li like a box but a polygon
            \row
                \li \l {FrictionJoint}{FrictionJoint}
                \li like a box but a polygon
            \row
                \li \l {WheelJoint}{WheelJoint}
                \li like a box but a polygon
            \row
                \li \l {MouseJoint}{MouseJoint}
                \li like a box but a polygon
            \row
                \li \l {GearJoint}{GearJoint}
                \li like a box but a polygon
            \row
                \li \l {RopeJoint}{RopeJoint}
                \li like a box but a polygon
    \endtable
*/

////////////////////////////

/*!
\qmlproperty bool Joint::collideConnected
    Allows one to set the Joints of the respected bodys to allow colliding on connection.
*/

/*!
\qmlproperty string Joint::world
    The World that the Joints will be placed in.
*/

/*!
\qmlproperty string Joint::bodyA
    The first \l{Body}{body} in the joint connection
*/

/*!
\qmlproperty string Joint::bodyB
    The second \l{Body}{body} in the joint connection
*/

Box2DJoint::Box2DJoint(JointType jointType, QObject *parent) :
    QObject(parent),
    mJointType(jointType),
    mCollideConnected(false),
    mComponentComplete(false),
    mInitializePending(false),
    mBodyA(0),
    mBodyB(0),
    mWorld(0),
    mJoint(0)
{
}

Box2DJoint::~Box2DJoint()
{
    if (mJoint)
        mWorld->world().DestroyJoint(mJoint);
}

void Box2DJoint::setCollideConnected(bool collideConnected)
{
    if (mCollideConnected == collideConnected)
        return;

    mCollideConnected = collideConnected;

    emit collideConnectedChanged();
}

void Box2DJoint::setBodyA(Box2DBody *bodyA)
{
    if (mBodyA == bodyA)
        return;

    mBodyA = bodyA;

    if (!bodyA || bodyA->body())
        initialize();
    else
        connect(bodyA, SIGNAL(bodyCreated()), this, SLOT(bodyACreated()));

    emit bodyAChanged();
}

void Box2DJoint::setBodyB(Box2DBody *bodyB)
{
    if (mBodyB == bodyB)
        return;

    mBodyB = bodyB;

    if (!bodyB || bodyB->body())
        initialize();
    else
        connect(bodyB, SIGNAL(bodyCreated()), this, SLOT(bodyBCreated()));

    emit bodyBChanged();
}

void Box2DJoint::initialize()
{
    // Delay initialization until the component is complete
    if (!mComponentComplete) {
        mInitializePending = true;
        return;
    }
    mInitializePending = false;

    // Destroy any previously created joint
    if (mJoint) {
        mWorld->world().DestroyJoint(mJoint);
        mJoint = 0;
        mWorld = 0;
    }

    if (!mBodyA || !mBodyB)
        return;
    if (!mBodyA->body() || !mBodyB->body())
        return;

    if (mBodyA->world() != mBodyB->world()) {
        qWarning() << "Joint: bodyA and bodyB are not from the same world";
        return;
    }

    if (mBodyA == mBodyB) {
        qWarning() << "Joint: bodyA and bodyB cannot be the same body";
        return;
    }

    mWorld = mBodyA->world();
    mJoint = createJoint();
    if (mJoint)
        emit created();
}

void Box2DJoint::componentComplete()
{
    mComponentComplete = true;
    if (mInitializePending)
        initialize();
}

void Box2DJoint::initializeJointDef(b2JointDef &def)
{
    def.userData = this;
    def.bodyA = bodyA()->body();
    def.bodyB = bodyB()->body();
    def.collideConnected = mCollideConnected;
}

void Box2DJoint::bodyACreated()
{
    disconnect(mBodyA, SIGNAL(bodyCreated()), this, SLOT(bodyACreated()));
    initialize();
}

void Box2DJoint::bodyBCreated()
{
    disconnect(mBodyB, SIGNAL(bodyCreated()), this, SLOT(bodyBCreated()));
    initialize();
}
