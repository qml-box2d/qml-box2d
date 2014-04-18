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

Box2DRevoluteJoint::Box2DRevoluteJoint(QObject *parent) :
    Box2DJoint(mRevoluteJointDef, parent),
    mAnchorsAuto(true)
{
}

float Box2DRevoluteJoint::lowerAngle() const
{
    return toDegrees(mRevoluteJointDef.lowerAngle);
}

void Box2DRevoluteJoint::setLowerAngle(float lowerAngle)
{
    float lowerAngleRad = toRadians(lowerAngle);
    if (mRevoluteJointDef.lowerAngle == lowerAngleRad)
        return;

    mRevoluteJointDef.lowerAngle = lowerAngleRad;
    if (revoluteJoint())
        revoluteJoint()->SetLimits(lowerAngleRad,
                                   mRevoluteJointDef.upperAngle);
    emit lowerAngleChanged();
}

float Box2DRevoluteJoint::upperAngle() const
{
    return toDegrees(mRevoluteJointDef.upperAngle);
}

void Box2DRevoluteJoint::setUpperAngle(float upperAngle)
{
    float upperAngleRad = toRadians(upperAngle);
    if (mRevoluteJointDef.upperAngle == upperAngleRad)
        return;

    mRevoluteJointDef.upperAngle = upperAngleRad;
    if (revoluteJoint())
        revoluteJoint()->SetLimits(mRevoluteJointDef.lowerAngle,
                                   upperAngleRad);
    emit upperAngleChanged();
}

void Box2DRevoluteJoint::setMaxMotorTorque(float maxMotorTorque)
{
    if (mRevoluteJointDef.maxMotorTorque == maxMotorTorque)
        return;

    mRevoluteJointDef.maxMotorTorque = maxMotorTorque;
    if (revoluteJoint())
        revoluteJoint()->SetMaxMotorTorque(maxMotorTorque);
    emit maxMotorTorqueChanged();
}

float Box2DRevoluteJoint::motorSpeed() const
{
    return toDegrees(mRevoluteJointDef.motorSpeed);
}

void Box2DRevoluteJoint::setMotorSpeed(float motorSpeed)
{
    const float motorSpeedRad = toRadians(motorSpeed);
    if (mRevoluteJointDef.motorSpeed == motorSpeedRad)
        return;

    mRevoluteJointDef.motorSpeed = motorSpeedRad;
    if (revoluteJoint())
        revoluteJoint()->SetMotorSpeed(motorSpeedRad);
    emit motorSpeedChanged();
}

void Box2DRevoluteJoint::setEnableLimit(bool enableLimit)
{
    if (mRevoluteJointDef.enableLimit == enableLimit)
        return;

    mRevoluteJointDef.enableLimit = enableLimit;
    if (revoluteJoint())
        revoluteJoint()->EnableLimit(enableLimit);
    emit enableLimitChanged();
}

void Box2DRevoluteJoint::setEnableMotor(bool enableMotor)
{
    if (mRevoluteJointDef.enableMotor == enableMotor)
        return;

    mRevoluteJointDef.enableMotor = enableMotor;
    if (revoluteJoint())
        revoluteJoint()->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

QPointF Box2DRevoluteJoint::localAnchorA() const
{
    return world()->toPixels(mRevoluteJointDef.localAnchorA);
}

QPointF Box2DRevoluteJoint::localAnchorB() const
{
    return world()->toPixels(mRevoluteJointDef.localAnchorB);
}

void Box2DRevoluteJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mRevoluteJointDef.localAnchorA = world()->toMeters(localAnchorA);
    mAnchorsAuto = false;
    emit localAnchorAChanged();
}

void Box2DRevoluteJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mRevoluteJointDef.localAnchorB = world()->toMeters(localAnchorB);
    mAnchorsAuto = false;
    emit localAnchorBChanged();
}

b2Joint *Box2DRevoluteJoint::createJoint()
{
    if (mAnchorsAuto) {
        mRevoluteJointDef.Initialize(mRevoluteJointDef.bodyA,
                                     mRevoluteJointDef.bodyB,
                                     mRevoluteJointDef.bodyA->GetWorldCenter());
    }

    return world()->world().CreateJoint(&mRevoluteJointDef);
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
