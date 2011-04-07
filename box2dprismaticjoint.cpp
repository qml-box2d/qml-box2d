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

#include "box2dprismaticjoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DPrismaticJoint::Box2DPrismaticJoint(QObject *parent) :
    Box2DJoint(parent),
    mPrismaticJointDef(),
    mPrismaticJoint(0)
{
}

Box2DPrismaticJoint::~Box2DPrismaticJoint()
{
    cleanup(world());
}

float Box2DPrismaticJoint::lowerTranslation() const
{
    return mPrismaticJointDef.lowerTranslation;
}

void Box2DPrismaticJoint::setLowerTranslation(float lowerTranslation)
{
    if (mPrismaticJointDef.lowerTranslation == lowerTranslation)
        return;

    mPrismaticJointDef.lowerTranslation = lowerTranslation;
    if (mPrismaticJoint)
        mPrismaticJoint->SetLimits(lowerTranslation,
                                   mPrismaticJointDef.upperTranslation);
    emit lowerTranslationChanged();
}

float Box2DPrismaticJoint::upperTranslation() const
{
    return mPrismaticJointDef.upperTranslation;
}

void Box2DPrismaticJoint::setUpperTranslation(float upperTranslation)
{
    if (mPrismaticJointDef.upperTranslation == upperTranslation)
        return;

    mPrismaticJointDef.upperTranslation = upperTranslation;
    if (mPrismaticJoint)
        mPrismaticJoint->SetLimits(mPrismaticJointDef.lowerTranslation,
                                   upperTranslation);
    emit upperTranslationChanged();
}

float Box2DPrismaticJoint::maxMotorForce() const
{
    return mPrismaticJointDef.maxMotorForce;
}

void Box2DPrismaticJoint::setMaxMotorForce(float maxMotorForce)
{
    if (mPrismaticJointDef.maxMotorForce == maxMotorForce)
        return;

    mPrismaticJointDef.maxMotorForce = maxMotorForce;
    if (mPrismaticJoint)
        mPrismaticJoint->SetMaxMotorForce(maxMotorForce);
    emit maxMotorForceChanged();
}

float Box2DPrismaticJoint::motorSpeed() const
{
    return mPrismaticJointDef.motorSpeed;
}

void Box2DPrismaticJoint::setMotorSpeed(float motorSpeed)
{
    if (mPrismaticJointDef.motorSpeed == motorSpeed)
        return;

    mPrismaticJointDef.motorSpeed = motorSpeed;
    if (mPrismaticJoint)
        mPrismaticJoint->SetMotorSpeed(motorSpeed);
    emit motorSpeedChanged();
}

bool Box2DPrismaticJoint::enableLimit() const
{
    return mPrismaticJointDef.enableLimit;
}

void Box2DPrismaticJoint::setEnableLimit(bool enableLimit)
{
    if (mPrismaticJointDef.enableLimit == enableLimit)
        return;

    mPrismaticJointDef.enableLimit = enableLimit;
    if (mPrismaticJoint)
        mPrismaticJoint->EnableLimit(enableLimit);
    emit enableLimitChanged();
}

bool Box2DPrismaticJoint::enableMotor() const
{
    return mPrismaticJointDef.enableMotor;
}

void Box2DPrismaticJoint::setEnableMotor(bool enableMotor)
{
    if (mPrismaticJointDef.enableMotor == enableMotor)
        return;

    mPrismaticJointDef.enableMotor = enableMotor;
    if (mPrismaticJoint)
        mPrismaticJoint->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

QPointF Box2DPrismaticJoint::axis() const
{
    return QPointF(mPrismaticJointDef.localAxis1.x,
                   -mPrismaticJointDef.localAxis1.y);
}

void Box2DPrismaticJoint::setAxis(const QPointF &axis)
{
    if (mPrismaticJointDef.localAxis1 == b2Vec2(axis.x(), -axis.y()))
        return;

    mPrismaticJointDef.localAxis1 = b2Vec2(axis.x(), -axis.y());

    emit axisChanged();
}

void Box2DPrismaticJoint::nullifyJoint()
{
    mPrismaticJoint = 0;
}

void Box2DPrismaticJoint::createJoint()
{
    mPrismaticJointDef.Initialize(bodyA()->body(), bodyB()->body(),
                                 bodyA()->body()->GetWorldCenter(),
                                  mPrismaticJointDef.localAxis1);
    mPrismaticJointDef.collideConnected = collideConnected();

    mPrismaticJoint = static_cast<b2PrismaticJoint*>
            (world()->CreateJoint(&mPrismaticJointDef));
    mPrismaticJoint->SetUserData(this);
    mInitializePending = false;
}

void Box2DPrismaticJoint::cleanup(b2World *world)
{
    if (mPrismaticJoint && bodyA() && bodyB()) {
        mPrismaticJoint->SetUserData(0);
        world->DestroyJoint(mPrismaticJoint);
        mPrismaticJoint = 0;
    }
}
