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

Box2DMotorJoint::Box2DMotorJoint(QObject *parent) :
    Box2DJoint(mMotorJointDef, parent)
{
}

QPointF Box2DMotorJoint::linearOffset() const
{
    return world()->toPixels(mMotorJointDef.linearOffset);
}

void Box2DMotorJoint::setLinearOffset(const QPointF &linearOffset)
{
    const b2Vec2 linearOffsetMeters = world()->toMeters(linearOffset);
    if (mMotorJointDef.linearOffset == linearOffsetMeters)
        return;

    mMotorJointDef.linearOffset = linearOffsetMeters;
    if (motorJoint())
        motorJoint()->SetLinearOffset(linearOffsetMeters);
    emit linearOffsetChanged();
}

float Box2DMotorJoint::angularOffset() const
{
    return toDegrees(mMotorJointDef.angularOffset);
}

void Box2DMotorJoint::setAngularOffset(float angularOffset)
{
    const float angularOffsetRad = toRadians(angularOffset);
    if (mMotorJointDef.angularOffset == angularOffsetRad)
        return;

    mMotorJointDef.angularOffset = angularOffsetRad;
    if (motorJoint())
        motorJoint()->SetAngularOffset(angularOffsetRad);
    emit angularOffsetChanged();
}

void Box2DMotorJoint::setMaxForce(float maxForce)
{
    if (mMotorJointDef.maxForce == maxForce)
        return;

    mMotorJointDef.maxForce = maxForce;
    if (motorJoint())
        motorJoint()->SetMaxForce(maxForce);
    emit maxForceChanged();
}

void Box2DMotorJoint::setMaxTorque(float maxTorque)
{
    if (mMotorJointDef.maxTorque == maxTorque)
        return;

    mMotorJointDef.maxTorque = maxTorque;
    if (motorJoint())
        motorJoint()->SetMaxTorque(maxTorque);
    emit maxTorqueChanged();
}

void Box2DMotorJoint::setCorrectionFactor(float correctionFactor)
{
    if (mMotorJointDef.correctionFactor == correctionFactor)
        return;

    mMotorJointDef.correctionFactor = correctionFactor;
    if (motorJoint())
        motorJoint()->SetCorrectionFactor(correctionFactor);
    emit correctionFactorChanged();
}

b2Joint *Box2DMotorJoint::createJoint()
{
    mMotorJointDef.Initialize(bodyA()->body(), bodyB()->body());

    return world()->world().CreateJoint(&mMotorJointDef);
}
