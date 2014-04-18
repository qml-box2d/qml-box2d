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

Box2DWheelJoint::Box2DWheelJoint(QObject *parent) :
    Box2DJoint(mWheelJointDef, parent),
    mAnchorsAuto(true)
{
}

void Box2DWheelJoint::setDampingRatio(float dampingRatio)
{
    if (mWheelJointDef.dampingRatio == dampingRatio)
        return;

    mWheelJointDef.dampingRatio = dampingRatio;
    if (wheelJoint())
        wheelJoint()->SetSpringDampingRatio(dampingRatio);
    emit dampingRatioChanged();
}

void Box2DWheelJoint::setFrequencyHz(float frequencyHz)
{
    if (mWheelJointDef.frequencyHz == frequencyHz)
        return;

    mWheelJointDef.frequencyHz = frequencyHz;
    if (wheelJoint())
        wheelJoint()->SetSpringFrequencyHz(frequencyHz);
    emit frequencyHzChanged();
}

void Box2DWheelJoint::setMaxMotorTorque(float maxMotorTorque)
{
    if (mWheelJointDef.maxMotorTorque == maxMotorTorque)
        return;

    mWheelJointDef.maxMotorTorque = maxMotorTorque;
    if (wheelJoint())
        wheelJoint()->SetMaxMotorTorque(maxMotorTorque);
    emit maxMotorTorqueChanged();
}

float Box2DWheelJoint::motorSpeed() const
{
    return toDegrees(mWheelJointDef.motorSpeed);
}

void Box2DWheelJoint::setMotorSpeed(float motorSpeed)
{
    float motorSpeedRad = toRadians(motorSpeed);
    if (mWheelJointDef.motorSpeed == motorSpeedRad)
        return;

    mWheelJointDef.motorSpeed = motorSpeedRad;
    if (wheelJoint())
        wheelJoint()->SetMotorSpeed(motorSpeedRad);
    emit motorSpeedChanged();
}

void Box2DWheelJoint::setEnableMotor(bool enableMotor)
{
    if (mWheelJointDef.enableMotor == enableMotor)
        return;

    mWheelJointDef.enableMotor = enableMotor;
    if (wheelJoint())
        wheelJoint()->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

QPointF Box2DWheelJoint::localAnchorA() const
{
    return world()->toPixels(mWheelJointDef.localAnchorA);
}

void Box2DWheelJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mWheelJointDef.localAnchorA = world()->toMeters(localAnchorA);
    mAnchorsAuto = false;
    emit localAnchorAChanged();
}

QPointF Box2DWheelJoint::localAnchorB() const
{
    return world()->toPixels(mWheelJointDef.localAnchorB);
}

void Box2DWheelJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mWheelJointDef.localAnchorB = world()->toMeters(localAnchorB);
    mAnchorsAuto = false;
    emit localAnchorBChanged();
}

QPointF Box2DWheelJoint::localAxisA() const
{
    return world()->toPixels(mWheelJointDef.localAxisA);
}

void Box2DWheelJoint::setLocalAxisA(const QPointF &localAxisA)
{
    mWheelJointDef.localAxisA = world()->toMeters(localAxisA);
    mAnchorsAuto = false;
    emit localAxisAChanged();
}

b2Joint *Box2DWheelJoint::createJoint()
{
    if (mAnchorsAuto) {
        mWheelJointDef.Initialize(mWheelJointDef.bodyA,
                                  mWheelJointDef.bodyB,
                                  mWheelJointDef.bodyA->GetWorldCenter(),
                                  mWheelJointDef.localAxisA);
    }

    return world()->world().CreateJoint(&mWheelJointDef);
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
