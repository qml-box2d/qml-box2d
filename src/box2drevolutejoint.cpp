/*
 * box2drevolutejoint.cpp
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2011 Markus Kivioja <markus.kivioja@digia.com>
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

#include "box2drevolutejoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

/*!
   \qmltype RevoluteJoint
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
   \brief A RevoluteJoint forces two \l {Body} {bodies} to share a common anchor point, often
 called a hinge point.
The revolute joint has a single degree of freedom: the relative rotation of the two bodies.
This is called the jointAngle.

To specify a RevoluteJoint you need to provide two \l {Body} {bodies} and two anchor points
    \list
        \li  \l {RevoluteJoint::localAnchorA}{localAnchorA }
        \li \l {RevoluteJoint::localAnchorB}{localAnchorB }
    \endlist

One also has to provide the \l {World}{ world space}. The initialization function assumes that
the bodies are already in the correct position.

In this \l {revolute}{example}, two bodies are connected via a RevoluteJoint

A RevoluteJoint can have a
    \{RevoluteJoint::motorEnabled} {motor}
    which can  allow you to specify the
    \list
        \li \l {RevoluteJoint::motorSpeed}{motorSpeed}
        \li \l {RevoluteJoint::maxMotorTorque}{maxMotorTorque}
    \endlist

The speed can be negative or positive. A motor can have infinite force, but this is usually
not desirable.

\code
        RevoluteJoint {
            id: revolute
            maxMotorTorque: 1000
            motorSpeed: 40
            enableMotor: false
            bodyA: middle
            bodyB: rod
            world: world
            localAnchorA: Qt.point(20,20)
            localAnchorB: Qt.point(40,20)
        }
\endcode

*/

/*!
 \qmlproperty QPointF RevoluteJoint::localAnchorA
  The first body that is connected to Revolute system.
     \code
    World{
        id: world
        anchor.fill:parent
        Body{
            id: bodyA
            ...
            ......
        RevoluteJoint {
            world: world
            bodyA: bodyA
            ....
            ........
            }
    \endcode
 */
/*!
 \qmlproperty QPointF RevoluteJoint::localAnchorB
   The second body that is connected to Revolute system.
    \code
    World{
        id: world
        anchor.fill:parent
        Body{
            id: bodyB
            ...
            ......
        RevoluteJoint {
            world: world
            bodyB: bodyB
            ....
            ........
            }
    \endcode

 */
/*!
 \qmlproperty float  RevoluteJoint::referenceAngle
DOCME
 */

/*!
 \qmlproperty float  RevoluteJoint::lowerAngle
DOCME
 */
/*!
 \qmlproperty float  RevoluteJoint::upperAngle
DOCME
 */

/*!
 \qmlproperty float  RevoluteJoint::maxMotorTorque
The maxium ammount of motor torque that can be applied to motor
 */
/*!
 \qmlproperty float RevoluteJoint::motorSpeed
If the motor is enabled . One can use this for the speed in which the motor runs at.
 */
/*!
 \qmlproperty bool RevoluteJoint::enableLimit
If set to true it will enable limits on the RevoluteJoint
 */
/*!
 \qmlproperty bool RevoluteJoint::enableMotor
 By making this true one can enable a motor on there RevoluteJoint
 */


Box2DRevoluteJoint::Box2DRevoluteJoint(QObject *parent)
    : Box2DJoint(RevoluteJoint, parent)
    , m_referenceAngle(0.0f)
    , m_enableLimit(false)
    , m_lowerAngle(0.0f)
    , m_upperAngle(0.0f)
    , m_enableMotor(false)
    , m_motorSpeed(0.0f)
    , m_maxMotorTorque(0.0f)
    , m_defaultLocalAnchorA(true)
    , m_defaultLocalAnchorB(true)
    , m_defaultReferenceAngle(true)
{
}

void Box2DRevoluteJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    m_defaultLocalAnchorA = false;

    if (m_localAnchorA == localAnchorA)
        return;

    m_localAnchorA = localAnchorA;
    emit localAnchorAChanged();
}

void Box2DRevoluteJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    m_defaultLocalAnchorB = false;

    if (m_localAnchorB == localAnchorB)
        return;

    m_localAnchorB = localAnchorB;
    emit localAnchorBChanged();
}

void Box2DRevoluteJoint::setReferenceAngle(float referenceAngle)
{
    m_defaultReferenceAngle = false;

    if (m_referenceAngle == referenceAngle)
        return;

    m_referenceAngle = referenceAngle;
    emit referenceAngleChanged();
}

void Box2DRevoluteJoint::setEnableLimit(bool enableLimit)
{
    if (m_enableLimit == enableLimit)
        return;

    m_enableLimit = enableLimit;
    if (revoluteJoint())
        revoluteJoint()->EnableLimit(enableLimit);
    emit enableLimitChanged();
}

void Box2DRevoluteJoint::setLowerAngle(float lowerAngle)
{
    if (m_lowerAngle == lowerAngle)
        return;

    m_lowerAngle = lowerAngle;
    if (revoluteJoint())
        revoluteJoint()->SetLimits(toRadians(lowerAngle),
                                   toRadians(m_upperAngle));
    emit lowerAngleChanged();
}

void Box2DRevoluteJoint::setUpperAngle(float upperAngle)
{
    if (m_upperAngle == upperAngle)
        return;

    m_upperAngle = upperAngle;
    if (revoluteJoint())
        revoluteJoint()->SetLimits(toRadians(m_lowerAngle),
                                   toRadians(upperAngle));
    emit upperAngleChanged();
}

void Box2DRevoluteJoint::setEnableMotor(bool enableMotor)
{
    if (m_enableMotor == enableMotor)
        return;

    m_enableMotor = enableMotor;
    if (revoluteJoint())
        revoluteJoint()->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

void Box2DRevoluteJoint::setMotorSpeed(float motorSpeed)
{
    if (m_motorSpeed == motorSpeed)
        return;

    m_motorSpeed = motorSpeed;
    if (revoluteJoint())
        revoluteJoint()->SetMotorSpeed(toRadians(motorSpeed));
    emit motorSpeedChanged();
}

void Box2DRevoluteJoint::setMaxMotorTorque(float maxMotorTorque)
{
    if (m_maxMotorTorque == maxMotorTorque)
        return;

    m_maxMotorTorque = maxMotorTorque;
    if (revoluteJoint())
        revoluteJoint()->SetMaxMotorTorque(maxMotorTorque);
    emit maxMotorTorqueChanged();
}

b2Joint *Box2DRevoluteJoint::createJoint()
{
    b2RevoluteJointDef jointDef;
    initializeJointDef(jointDef);

    // Default localAnchorA to bodyA center
    if (m_defaultLocalAnchorA)
        jointDef.localAnchorA = jointDef.bodyA->GetLocalCenter();
    else
        jointDef.localAnchorA = world()->toMeters(m_localAnchorA);

    // Default localAnchorB to the same world position as localAnchorA
    if (m_defaultLocalAnchorB) {
        b2Vec2 anchorA = jointDef.bodyA->GetWorldPoint(jointDef.localAnchorA);
        jointDef.localAnchorB = jointDef.bodyB->GetLocalPoint(anchorA);
    } else {
        jointDef.localAnchorB = world()->toMeters(m_localAnchorB);
    }

    if (m_defaultReferenceAngle) {
        float32 angleA = jointDef.bodyA->GetAngle();
        float32 angleB = jointDef.bodyB->GetAngle();
        jointDef.referenceAngle = angleB - angleA;
    } else {
        jointDef.referenceAngle = toRadians(m_referenceAngle);
    }

    jointDef.enableLimit = m_enableLimit;
    jointDef.lowerAngle = toRadians(m_lowerAngle);
    jointDef.upperAngle = toRadians(m_upperAngle);
    jointDef.enableMotor = m_enableMotor;
    jointDef.motorSpeed = toRadians(m_motorSpeed);
    jointDef.maxMotorTorque = m_maxMotorTorque;

    return world()->world().CreateJoint(&jointDef);
}

/*!
 \qmlmethod RevoluteJoint::getJointAngle()
Returns the current RevoluteJoint angle.
*/
float Box2DRevoluteJoint::getJointAngle() const
{
    if (revoluteJoint())
        return toDegrees(revoluteJoint()->GetJointAngle());
    return 0.0;
}

/*!
 \qmlmethod Box2DRevoluteJoint::getJointSpeed()
Returns the joints speed
 */
float Box2DRevoluteJoint::getJointSpeed() const
{
    if (revoluteJoint())
        return revoluteJoint()->GetJointSpeed();
    return 0.0;
}
