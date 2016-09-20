/*
 * box2dmotorjoint.cpp
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

#include "box2dmotorjoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DMotorJoint::Box2DMotorJoint(QObject *parent)
    : Box2DJoint(MotorJoint, parent)
    , m_angularOffset(0.0f)
    , m_maxForce(1.0f)
    , m_maxTorque(1.0f)
    , m_correctionFactor(0.3f)
    , m_defaultLinearOffset(true)
    , m_defaultAngularOffset(true)
{
}

void Box2DMotorJoint::setLinearOffset(const QPointF &linearOffset)
{
    m_defaultLinearOffset = false;

    if (m_linearOffset == linearOffset)
        return;

    m_linearOffset = linearOffset;
    if (motorJoint())
        motorJoint()->SetLinearOffset(world()->toMeters(linearOffset));
    emit linearOffsetChanged();
}

void Box2DMotorJoint::setAngularOffset(float angularOffset)
{
    m_defaultAngularOffset = false;

    if (m_angularOffset == angularOffset)
        return;

    m_angularOffset = angularOffset;
    if (motorJoint())
        motorJoint()->SetAngularOffset(toRadians(angularOffset));
    emit angularOffsetChanged();
}

void Box2DMotorJoint::setMaxForce(float maxForce)
{
    if (m_maxForce == maxForce)
        return;

    m_maxForce = maxForce;
    if (motorJoint())
        motorJoint()->SetMaxForce(maxForce);
    emit maxForceChanged();
}

void Box2DMotorJoint::setMaxTorque(float maxTorque)
{
    if (m_maxTorque == maxTorque)
        return;

    m_maxTorque = maxTorque;
    if (motorJoint())
        motorJoint()->SetMaxTorque(maxTorque);
    emit maxTorqueChanged();
}

void Box2DMotorJoint::setCorrectionFactor(float correctionFactor)
{
    if (m_correctionFactor == correctionFactor)
        return;

    m_correctionFactor = correctionFactor;
    if (motorJoint())
        motorJoint()->SetCorrectionFactor(correctionFactor);
    emit correctionFactorChanged();
}

b2Joint *Box2DMotorJoint::createJoint()
{
    b2MotorJointDef jointDef;
    initializeJointDef(jointDef);

    if (m_defaultLinearOffset) {
        const b2Vec2 &positionB = jointDef.bodyB->GetPosition();
        jointDef.linearOffset = jointDef.bodyA->GetLocalPoint(positionB);
    } else {
        jointDef.linearOffset = world()->toMeters(m_linearOffset);
    }

    if (m_defaultAngularOffset) {
        float32 angleA = jointDef.bodyA->GetAngle();
        float32 angleB = jointDef.bodyB->GetAngle();
        jointDef.angularOffset = angleB - angleA;
    } else {
        jointDef.angularOffset = toRadians(m_angularOffset);
    }

    jointDef.maxForce = m_maxForce;
    jointDef.maxTorque = m_maxTorque;
    jointDef.correctionFactor = m_correctionFactor;

    return world()->world().CreateJoint(&jointDef);
}
