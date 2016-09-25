/*
 * box2dprismaticjoint.cpp
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

#include "box2dprismaticjoint.h"

#include "box2dworld.h"

/*!
   \qmltype PrismaticJoint
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
    \brief A PrismaticJoint allows for relative translation of two bodies along a specified axis.

 A PrismaticJoint prevents relative rotation. Therefore, a PrismaticJoint has a single degree of freedom.

The PrismaticJoint definition is similar to the RevoluteJoint description; just substitute
translation for \c axis and \c maxMotorForce for \c maxMotorTorque. Using this analogy provides
an example

PrismaticJoint definition with a Joint limit and a friction motor:
\code
        PrismaticJoint {
            id: prismatic
            lowerTranslation: -250
            upperTranslation: 150
            enableLimit: true
            maxMotorForce: 3000
            motorSpeed: -100
            enableMotor: true
            bodyB: square
            bodyA: middle
            axis: Qt.point(100, 40)
            world: world
        }
\endcode

The RevoluteJoint has an implicit axis coming out of the screen. The PrismaticJoint needs
an explicit axis parallel to the screen. This axis is fixed in the two \l {Body} {bodies} and follows
 their motion. Like the RevoluteJoint, the PrismaticJoint translation is zero
 also see the \l {prismatic} {Prismatic Example }
*/


/*!
 \qmlproperty float PrismaticJoint::localAnchorA
    The local anchor point associated with bodyA
 */
/*!
 \qmlproperty Qt.point PrismaticJoint::localAnchorB
    The local anchor point associated with bodyb
 */
/*!
 \qmlproperty Qt.point PrismaticJoint::localAxisA
    The axis of the current Prismatic two joints
 */
/*!
 \qmlproperty float PrismaticJoint::referenceAngle
    DOCME
 */
/*!
 \qmlproperty bool PrismaticJoint::enableLimit
   Set to true to enable limiting on the joints .
 */
/*!
 \qmlproperty float PrismaticJoint::lowerTranslation
The lower translation between the two joints

 */
/*!
 \qmlproperty float PrismaticJoint::upperTranslation
    The upper translation between the two joints
 */
/*!
 \qmlproperty bool PrismaticJoint::enableMotor
  Set to true to enable a motor on the joints.
 */
/*!
 \qmlproperty float PrismaticJoint::maxMotorForce
    The maxium allowed motor force that you PrismaticJoint will use.
 */
/*!
 \qmlproperty float PrismaticJoint::motorSpeed
    The maxium ammount of motor speed that will be used.
 */

Box2DPrismaticJoint::Box2DPrismaticJoint(QObject *parent)
    : Box2DJoint(PrismaticJoint, parent)
    , m_localAxisA(1.0, 0.0)
    , m_referenceAngle(0.0f)
    , m_enableLimit(false)
    , m_lowerTranslation(0.0f)
    , m_upperTranslation(0.0f)
    , m_enableMotor(false)
    , m_maxMotorForce(0.0f)
    , m_motorSpeed(0.0f)
    , m_defaultLocalAnchorA(true)
    , m_defaultLocalAnchorB(true)
    , m_defaultReferenceAngle(true)
{
}

void Box2DPrismaticJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    m_defaultLocalAnchorA = false;

    if (m_localAnchorA == localAnchorA)
        return;

    m_localAnchorA = localAnchorA;
    emit localAnchorAChanged();
}

void Box2DPrismaticJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    m_defaultLocalAnchorB = false;

    if (m_localAnchorB == localAnchorB)
        return;

    m_localAnchorB = localAnchorB;
    emit localAnchorBChanged();
}

void Box2DPrismaticJoint::setLocalAxisA(const QPointF &localAxisA)
{
    if (m_localAxisA == localAxisA)
        return;

    m_localAxisA = localAxisA;
    emit localAxisAChanged();
}

void Box2DPrismaticJoint::setLowerTranslation(float lowerTranslation)
{
    if (m_lowerTranslation == lowerTranslation)
        return;

    m_lowerTranslation = lowerTranslation;
    if (prismaticJoint()) {
        prismaticJoint()->SetLimits(world()->toMeters(lowerTranslation),
                                    prismaticJoint()->GetUpperLimit());
    }
    emit lowerTranslationChanged();
}

void Box2DPrismaticJoint::setUpperTranslation(float upperTranslation)
{
    if (m_upperTranslation == upperTranslation)
        return;

    m_upperTranslation = upperTranslation;
    if (prismaticJoint()) {
        prismaticJoint()->SetLimits(prismaticJoint()->GetLowerLimit(),
                                    world()->toMeters(upperTranslation));
    }
    emit upperTranslationChanged();
}

void Box2DPrismaticJoint::setMaxMotorForce(float maxMotorForce)
{
    if (m_maxMotorForce == maxMotorForce)
        return;

    m_maxMotorForce = maxMotorForce;
    if (prismaticJoint())
        prismaticJoint()->SetMaxMotorForce(maxMotorForce);
    emit maxMotorForceChanged();
}

void Box2DPrismaticJoint::setMotorSpeed(float motorSpeed)
{
    if (m_motorSpeed == motorSpeed)
        return;

    m_motorSpeed = motorSpeed;
    if (prismaticJoint())
        prismaticJoint()->SetMotorSpeed(toRadians(motorSpeed));
    emit motorSpeedChanged();
}

void Box2DPrismaticJoint::setEnableLimit(bool enableLimit)
{
    if (m_enableLimit == enableLimit)
        return;

    m_enableLimit = enableLimit;
    if (prismaticJoint())
        prismaticJoint()->EnableLimit(enableLimit);
    emit enableLimitChanged();
}

void Box2DPrismaticJoint::setEnableMotor(bool enableMotor)
{
    if (m_enableMotor == enableMotor)
        return;

    m_enableMotor = enableMotor;
    if (prismaticJoint())
        prismaticJoint()->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

void Box2DPrismaticJoint::setReferenceAngle(float referenceAngle)
{
    m_defaultReferenceAngle = false;

    if (m_referenceAngle == referenceAngle)
        return;

    m_referenceAngle = referenceAngle;
    emit referenceAngleChanged();
}

b2Joint *Box2DPrismaticJoint::createJoint()
{
    b2PrismaticJointDef jointDef;
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

    jointDef.localAxisA = invertY(m_localAxisA);

    if (m_defaultReferenceAngle) {
        float32 angleA = jointDef.bodyA->GetAngle();
        float32 angleB = jointDef.bodyB->GetAngle();
        jointDef.referenceAngle = angleB - angleA;
    } else {
        jointDef.referenceAngle = toRadians(m_referenceAngle);
    }

    jointDef.enableLimit = m_enableLimit;
    jointDef.lowerTranslation = world()->toMeters(m_lowerTranslation);
    jointDef.upperTranslation = world()->toMeters(m_upperTranslation);
    jointDef.enableMotor = m_enableMotor;
    jointDef.maxMotorForce = m_maxMotorForce;
    jointDef.motorSpeed = toRadians(m_motorSpeed);

    return world()->world().CreateJoint(&jointDef);
}

/*!
 \qmlmethod PrismaticJoint::getJointTranslation()
    Returns the current translation for the prismatic joint.
 */
float Box2DPrismaticJoint::getJointTranslation() const
{
    if (prismaticJoint())
        return world()->toPixels(prismaticJoint()->GetJointTranslation());
    return 0.0f;
}
/*!
 \qmlmethod PrismaticJoint::getJointSpeed()
    Returns the current speed of the prismatic joint.
*/
float Box2DPrismaticJoint::getJointSpeed() const
{
    if (prismaticJoint())
        return prismaticJoint()->GetJointSpeed();
    return 0.0f;
}
