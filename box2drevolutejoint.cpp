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

float Box2DRevoluteJoint::getJointAngle() const
{
    if (revoluteJoint())
        return toDegrees(revoluteJoint()->GetJointAngle());
    return 0.0;
}

float Box2DRevoluteJoint::getJointSpeed() const
{
    if (revoluteJoint())
        return revoluteJoint()->GetJointSpeed();
    return 0.0;
}
