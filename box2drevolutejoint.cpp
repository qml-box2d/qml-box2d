/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the Box2D QML plugin.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library;  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2drevolutejoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DRevoluteJoint::Box2DRevoluteJoint(QObject *parent) :
    Box2DJoint(parent),
    mRevoluteJointDef(),
    mRevoluteJoint(0),
    mOverrideLocalAnchorA(false)
{
}

Box2DRevoluteJoint::~Box2DRevoluteJoint()
{
    cleanup(world());
}

float Box2DRevoluteJoint::lowerAngle() const
{
    return mRevoluteJointDef.lowerAngle;
}

void Box2DRevoluteJoint::setLowerAngle(float lowerAngle)
{
    if (mRevoluteJointDef.lowerAngle == lowerAngle * b2_pi)
        return;

    mRevoluteJointDef.lowerAngle = lowerAngle * b2_pi;
    if (mRevoluteJoint)
        mRevoluteJoint->SetLimits(lowerAngle * b2_pi,
                                  mRevoluteJointDef.upperAngle);
    emit lowerAngleChanged();
}

float Box2DRevoluteJoint::upperAngle() const
{
    return mRevoluteJointDef.upperAngle;
}

void Box2DRevoluteJoint::setUpperAngle(float upperAngle)
{
    if (mRevoluteJointDef.upperAngle == upperAngle * b2_pi)
        return;

    mRevoluteJointDef.upperAngle = upperAngle * b2_pi;
    if (mRevoluteJoint)
        mRevoluteJoint->SetLimits(mRevoluteJointDef.lowerAngle,
                                  upperAngle * b2_pi);
    emit upperAngleChanged();
}

float Box2DRevoluteJoint::maxMotorTorque() const
{
    return mRevoluteJointDef.maxMotorTorque;
}

void Box2DRevoluteJoint::setMaxMotorTorque(float maxMotorTorque)
{
    if (mRevoluteJointDef.maxMotorTorque == maxMotorTorque)
        return;

    mRevoluteJointDef.maxMotorTorque = maxMotorTorque;
    if (mRevoluteJoint)
        mRevoluteJoint->SetMaxMotorTorque(maxMotorTorque);
    emit maxMotorTorqueChanged();
}

float Box2DRevoluteJoint::motorSpeed() const
{
    return mRevoluteJointDef.motorSpeed;
}

void Box2DRevoluteJoint::setMotorSpeed(float motorSpeed)
{
    if (mRevoluteJointDef.motorSpeed == motorSpeed)
        return;

    mRevoluteJointDef.motorSpeed = motorSpeed;
    if (mRevoluteJoint)
        mRevoluteJoint->SetMotorSpeed(motorSpeed);
    emit motorSpeedChanged();
}

bool Box2DRevoluteJoint::enableLimit() const
{
    return mRevoluteJointDef.enableLimit;
}

void Box2DRevoluteJoint::setEnableLimit(bool enableLimit)
{
    if (mRevoluteJointDef.enableLimit == enableLimit)
        return;

    mRevoluteJointDef.enableLimit = enableLimit;
    if (mRevoluteJoint)
        mRevoluteJoint->EnableLimit(enableLimit);
    emit enableLimitChanged();
}

bool Box2DRevoluteJoint::enableMotor() const
{
    return mRevoluteJointDef.enableMotor;
}

void Box2DRevoluteJoint::setEnableMotor(bool enableMotor)
{
    if (mRevoluteJointDef.enableMotor == enableMotor)
        return;

    mRevoluteJointDef.enableMotor = enableMotor;
    if (mRevoluteJoint)
        mRevoluteJoint->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

QPointF Box2DRevoluteJoint::localAnchorA() const
{
    if (mOverrideLocalAnchorA)
        return mLocalAnchorA;
    else
        return QPointF(mRevoluteJointDef.localAnchorA.x * scaleRatio,
                       -mRevoluteJointDef.localAnchorA.y * scaleRatio);
}

void Box2DRevoluteJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    if (mOverrideLocalAnchorA && mLocalAnchorA == localAnchorA)
        return;

    mOverrideLocalAnchorA = true;
    mLocalAnchorA = localAnchorA;

    emit localAnchorAChanged();
}

void Box2DRevoluteJoint::nullifyJoint()
{
    mRevoluteJoint = 0;
}

void Box2DRevoluteJoint::createJoint()
{
    b2Vec2 anchor = mOverrideLocalAnchorA ?
                b2Vec2(mLocalAnchorA.x() / scaleRatio,
                       -mLocalAnchorA.y() / scaleRatio) +
                bodyA()->body()->GetPosition() :
                bodyA()->body()->GetWorldCenter();

    mRevoluteJointDef.Initialize(bodyA()->body(), bodyB()->body(),
                                 anchor);
    mRevoluteJointDef.collideConnected = collideConnected();

    mRevoluteJoint = static_cast<b2RevoluteJoint*>(
                world()->CreateJoint(&mRevoluteJointDef));
    mRevoluteJoint->SetUserData(this);
    mInitializePending = false;
}

void Box2DRevoluteJoint::cleanup(b2World *world)
{
    if (mRevoluteJoint && bodyA() && bodyB()) {
        mRevoluteJoint->SetUserData(0);
        world->DestroyJoint(mRevoluteJoint);
        mRevoluteJoint = 0;
    }
}
