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

void Box2DWheelJoint::setMotorSpeed(float motorSpeed)
{
    float motorSpeedRad = motorSpeed  * b2_pi / -180;
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
    return QPointF(mWheelJointDef.localAnchorA.x * scaleRatio,
                   -mWheelJointDef.localAnchorA.y * scaleRatio);
}

void Box2DWheelJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mWheelJointDef.localAnchorA = b2Vec2(localAnchorA.x() / scaleRatio,
                                         -localAnchorA.y() / scaleRatio);
    mAnchorsAuto = false;
    emit localAnchorAChanged();
}

QPointF Box2DWheelJoint::localAnchorB() const
{
    return QPointF(mWheelJointDef.localAnchorB.x * scaleRatio,
                   -mWheelJointDef.localAnchorB.y * scaleRatio);
}

void Box2DWheelJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mWheelJointDef.localAnchorB = b2Vec2(localAnchorB.x() / scaleRatio,
                                         -localAnchorB.y() / scaleRatio);
    mAnchorsAuto = false;
    emit localAnchorBChanged();
}

QPointF Box2DWheelJoint::localAxisA() const
{
    return QPointF(mWheelJointDef.localAxisA.x * scaleRatio,
                   -mWheelJointDef.localAxisA.y * scaleRatio);
}

void Box2DWheelJoint::setLocalAxisA(const QPointF &localAxisA)
{
    mWheelJointDef.localAnchorB = b2Vec2(localAxisA.x() / scaleRatio,
                                         -localAxisA.y() / scaleRatio);
    mAnchorsAuto = false;
    emit localAxisAChanged();
}


b2Joint *Box2DWheelJoint::createJoint()
{
    if (mAnchorsAuto) {
        mWheelJointDef.Initialize(bodyA()->body(),
                                  bodyB()->body(),
                                  bodyA()->body()->GetWorldCenter(),
                                  mWheelJointDef.localAxisA);
    } else {
        mWheelJointDef.bodyA = bodyA()->body();
        mWheelJointDef.bodyB = bodyB()->body();
    }

    return world()->CreateJoint(&mWheelJointDef);
}

float Box2DWheelJoint::getJointTranslation() const
{
    if (wheelJoint())
        return wheelJoint()->GetJointTranslation() * scaleRatio;
    return 0;
}

float Box2DWheelJoint::getJointSpeed() const
{
    if (wheelJoint())
        return wheelJoint()->GetJointSpeed() * scaleRatio;
    return 0;
}

QPointF Box2DWheelJoint::getReactionForce(float32 inv_dt) const
{
    if (wheelJoint()) {
        b2Vec2 point = wheelJoint()->GetReactionForce(inv_dt);
        return QPointF(point.x * scaleRatio,point.y * scaleRatio);
    }
    return QPointF();
}

float Box2DWheelJoint::getReactionTorque(float32 inv_dt) const
{
    if (wheelJoint())
        return wheelJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
