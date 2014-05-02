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

#include "box2dwheeljoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DWheelJoint::Box2DWheelJoint(QObject *parent)
    : Box2DJoint(WheelJoint, parent)
    , m_enableMotor(false)
    , m_maxMotorTorque(0.0f)
    , m_motorSpeed(0.0f)
    , m_frequencyHz(2.0f)
    , m_dampingRatio(0.7f)
    , m_defaultLocalAnchorA(true)
    , m_defaultLocalAnchorB(true)
    , m_defaultLocalAxisA(true)
{
}

void Box2DWheelJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    m_defaultLocalAnchorA = false;

    if (m_localAnchorA == localAnchorA)
        return;

    m_localAnchorA = localAnchorA;
    emit localAnchorAChanged();
}

void Box2DWheelJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    m_defaultLocalAnchorB = false;

    if (m_localAnchorB == localAnchorB)
        return;

    m_localAnchorB = localAnchorB;
    emit localAnchorBChanged();
}

void Box2DWheelJoint::setLocalAxisA(const QPointF &localAxisA)
{
    m_defaultLocalAxisA = false;

    if (m_localAxisA == localAxisA)
        return;

    m_localAxisA = localAxisA;
    emit localAxisAChanged();
}

void Box2DWheelJoint::setEnableMotor(bool enableMotor)
{
    if (m_enableMotor == enableMotor)
        return;

    m_enableMotor = enableMotor;
    if (wheelJoint())
        wheelJoint()->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

void Box2DWheelJoint::setMaxMotorTorque(float maxMotorTorque)
{
    if (m_maxMotorTorque == maxMotorTorque)
        return;

    m_maxMotorTorque = maxMotorTorque;
    if (wheelJoint())
        wheelJoint()->SetMaxMotorTorque(maxMotorTorque);
    emit maxMotorTorqueChanged();
}

void Box2DWheelJoint::setMotorSpeed(float motorSpeed)
{
    if (m_motorSpeed == motorSpeed)
        return;

    m_motorSpeed = motorSpeed;
    if (wheelJoint())
        wheelJoint()->SetMotorSpeed(toRadians(motorSpeed));
    emit motorSpeedChanged();
}

void Box2DWheelJoint::setFrequencyHz(float frequencyHz)
{
    if (m_frequencyHz == frequencyHz)
        return;

    m_frequencyHz = frequencyHz;
    if (wheelJoint())
        wheelJoint()->SetSpringFrequencyHz(frequencyHz);
    emit frequencyHzChanged();
}

void Box2DWheelJoint::setDampingRatio(float dampingRatio)
{
    if (m_dampingRatio == dampingRatio)
        return;

    m_dampingRatio = dampingRatio;
    if (wheelJoint())
        wheelJoint()->SetSpringDampingRatio(dampingRatio);
    emit dampingRatioChanged();
}

b2Joint *Box2DWheelJoint::createJoint()
{
    b2WheelJointDef jointDef;
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

    if (!m_defaultLocalAxisA) {
        jointDef.localAxisA = invertY(m_localAxisA);
        jointDef.localAxisA.Normalize();
    }

    jointDef.enableMotor = m_enableMotor;
    jointDef.maxMotorTorque = m_maxMotorTorque;
    jointDef.motorSpeed = toRadians(m_motorSpeed);
    jointDef.frequencyHz = m_frequencyHz;
    jointDef.dampingRatio = m_dampingRatio;

    return world()->world().CreateJoint(&jointDef);
}

float Box2DWheelJoint::getJointTranslation() const
{
    if (wheelJoint())
        return world()->toPixels(wheelJoint()->GetJointTranslation());
    return 0;
}

float Box2DWheelJoint::getJointSpeed() const
{
    if (wheelJoint())
        return wheelJoint()->GetJointSpeed();
    return 0;
}

QPointF Box2DWheelJoint::getReactionForce(float32 inv_dt) const
{
    if (wheelJoint())
        return invertY(wheelJoint()->GetReactionForce(inv_dt));
    return QPointF();
}

float Box2DWheelJoint::getReactionTorque(float32 inv_dt) const
{
    if (wheelJoint())
        return wheelJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
