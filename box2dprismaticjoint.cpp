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
#include "box2dbody.h"

Box2DPrismaticJoint::Box2DPrismaticJoint(QObject *parent) :
    Box2DJoint(parent),
    mPrismaticJointDef(),
    mPrismaticJoint(0),
    anchorsAuto(true)
{
}

Box2DPrismaticJoint::~Box2DPrismaticJoint()
{
    cleanup(world());
}

float Box2DPrismaticJoint::lowerTranslation() const
{
    return mPrismaticJointDef.lowerTranslation * scaleRatio;
}

void Box2DPrismaticJoint::setLowerTranslation(float lowerTranslation)
{
    if (qFuzzyCompare(mPrismaticJointDef.lowerTranslation,lowerTranslation / scaleRatio))
        return;
    mPrismaticJointDef.lowerTranslation = lowerTranslation / scaleRatio;
    if (mPrismaticJoint)
        mPrismaticJoint->SetLimits(mPrismaticJointDef.lowerTranslation,
                                   mPrismaticJointDef.upperTranslation);
    emit lowerTranslationChanged();
}

float Box2DPrismaticJoint::upperTranslation() const
{
    return mPrismaticJointDef.upperTranslation * scaleRatio;
}

void Box2DPrismaticJoint::setUpperTranslation(float upperTranslation)
{
    if (qFuzzyCompare(mPrismaticJointDef.upperTranslation,upperTranslation / scaleRatio))
        return;

    mPrismaticJointDef.upperTranslation = upperTranslation / scaleRatio;
    if (mPrismaticJoint)
        mPrismaticJoint->SetLimits(mPrismaticJointDef.lowerTranslation,
                                   mPrismaticJointDef.upperTranslation);
    emit upperTranslationChanged();
}

float Box2DPrismaticJoint::maxMotorForce() const
{
    return mPrismaticJointDef.maxMotorForce;
}

void Box2DPrismaticJoint::setMaxMotorForce(float maxMotorForce)
{
    if (qFuzzyCompare(mPrismaticJointDef.maxMotorForce,maxMotorForce))
        return;

    mPrismaticJointDef.maxMotorForce = maxMotorForce;
    if (mPrismaticJoint)
        mPrismaticJoint->SetMaxMotorForce(maxMotorForce);
    emit maxMotorForceChanged();
}

float Box2DPrismaticJoint::motorSpeed() const
{
    return mPrismaticJointDef.motorSpeed * scaleRatio;
}

void Box2DPrismaticJoint::setMotorSpeed(float motorSpeed)
{
    if (qFuzzyCompare(mPrismaticJointDef.motorSpeed,motorSpeed / scaleRatio))
        return;

    mPrismaticJointDef.motorSpeed = motorSpeed / scaleRatio;
    if (mPrismaticJoint)
        mPrismaticJoint->SetMotorSpeed(mPrismaticJointDef.motorSpeed);
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
    return QPointF(mPrismaticJointDef.localAxisA.x * scaleRatio,
                   -mPrismaticJointDef.localAxisA.y * scaleRatio);
}

void Box2DPrismaticJoint::setAxis(const QPointF &axis)
{
    mPrismaticJointDef.localAxisA = b2Vec2(axis.x() / scaleRatio, -axis.y() / scaleRatio);
    mPrismaticJointDef.localAxisA.Normalize();
    emit axisChanged();
}

QPointF Box2DPrismaticJoint::localAnchorA() const
{
    return QPointF(mPrismaticJointDef.localAnchorA.x * scaleRatio, mPrismaticJointDef.localAnchorA.y * scaleRatio);
}

QPointF Box2DPrismaticJoint::localAnchorB() const
{
    return QPointF(mPrismaticJointDef.localAnchorB.x * scaleRatio, mPrismaticJointDef.localAnchorB.y * scaleRatio);
}

void Box2DPrismaticJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mPrismaticJointDef.localAnchorA = b2Vec2(localAnchorA.x() / scaleRatio,-localAnchorA.y() / scaleRatio);
    anchorsAuto = false;
    emit localAnchorAChanged();
}

void Box2DPrismaticJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mPrismaticJointDef.localAnchorB = b2Vec2(localAnchorB.x() / scaleRatio,-localAnchorB.y() / scaleRatio);
    anchorsAuto = false;
    emit localAnchorBChanged();
}

void Box2DPrismaticJoint::nullifyJoint()
{
    mPrismaticJoint = 0;
}

void Box2DPrismaticJoint::createJoint()
{
    if(anchorsAuto)
        mPrismaticJointDef.Initialize(bodyA()->body(), bodyB()->body(),
                                 bodyA()->body()->GetWorldCenter(),
                                 mPrismaticJointDef.localAxisA);
    else
    {
        mPrismaticJointDef.bodyA = bodyA()->body();
        mPrismaticJointDef.bodyB = bodyB()->body();
        mPrismaticJointDef.referenceAngle = 0.0;
    }
    mPrismaticJointDef.collideConnected = collideConnected();

    mPrismaticJoint = static_cast<b2PrismaticJoint*>
            (world()->CreateJoint(&mPrismaticJointDef));
    mPrismaticJoint->SetUserData(this);
    mInitializePending = false;
    emit created();
}

void Box2DPrismaticJoint::cleanup(b2World *world)
{
    if(!world) {
        qWarning() << "PrismaticJoint: There is no world connected";
        return;
    }
    if (mPrismaticJoint && bodyA() && bodyB()) {
        mPrismaticJoint->SetUserData(0);
        world->DestroyJoint(mPrismaticJoint);
        mPrismaticJoint = 0;
    }
}

b2Joint *Box2DPrismaticJoint::GetJoint()
{
    return mPrismaticJoint;
}

float Box2DPrismaticJoint::GetJointTranslation()
{
    if(mPrismaticJoint) return mPrismaticJoint->GetJointTranslation() * scaleRatio;
    return 0.0;
}

float Box2DPrismaticJoint::GetJointSpeed()
{
    if(mPrismaticJoint) return mPrismaticJoint->GetJointSpeed();
    return 0.0;
}
