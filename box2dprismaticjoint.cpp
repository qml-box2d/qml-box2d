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
    Box2DJoint(mPrismaticJointDef, parent),
    mAnchorsAuto(true)
{
}

float Box2DPrismaticJoint::lowerTranslation() const
{
    return world()->toPixels(mPrismaticJointDef.lowerTranslation);
}

void Box2DPrismaticJoint::setLowerTranslation(float lowerTranslation)
{
    const float lowerTranslationMeters = world()->toMeters(lowerTranslation);
    if (mPrismaticJointDef.lowerTranslation == lowerTranslationMeters)
        return;

    mPrismaticJointDef.lowerTranslation = lowerTranslationMeters;
    if (prismaticJoint())
        prismaticJoint()->SetLimits(mPrismaticJointDef.lowerTranslation,
                                    mPrismaticJointDef.upperTranslation);
    emit lowerTranslationChanged();
}

float Box2DPrismaticJoint::upperTranslation() const
{
    return world()->toPixels(mPrismaticJointDef.upperTranslation);
}

void Box2DPrismaticJoint::setUpperTranslation(float upperTranslation)
{
    const float upperTranslationMeters = world()->toMeters(upperTranslation);
    if (mPrismaticJointDef.upperTranslation == upperTranslationMeters)
        return;

    mPrismaticJointDef.upperTranslation = upperTranslationMeters;
    if (prismaticJoint())
        prismaticJoint()->SetLimits(mPrismaticJointDef.lowerTranslation,
                                    mPrismaticJointDef.upperTranslation);
    emit upperTranslationChanged();
}

void Box2DPrismaticJoint::setMaxMotorForce(float maxMotorForce)
{
    if (mPrismaticJointDef.maxMotorForce == maxMotorForce)
        return;

    mPrismaticJointDef.maxMotorForce = maxMotorForce;
    if (prismaticJoint())
        prismaticJoint()->SetMaxMotorForce(maxMotorForce);
    emit maxMotorForceChanged();
}

float Box2DPrismaticJoint::motorSpeed() const
{
    return toDegrees(mPrismaticJointDef.motorSpeed);
}

void Box2DPrismaticJoint::setMotorSpeed(float motorSpeed)
{
    const float motorSpeedRad = toRadians(motorSpeed);
    if (mPrismaticJointDef.motorSpeed == motorSpeedRad)
        return;

    mPrismaticJointDef.motorSpeed = motorSpeedRad;
    if (prismaticJoint())
        prismaticJoint()->SetMotorSpeed(motorSpeedRad);
    emit motorSpeedChanged();
}

void Box2DPrismaticJoint::setEnableLimit(bool enableLimit)
{
    if (mPrismaticJointDef.enableLimit == enableLimit)
        return;

    mPrismaticJointDef.enableLimit = enableLimit;
    if (prismaticJoint())
        prismaticJoint()->EnableLimit(enableLimit);
    emit enableLimitChanged();
}

void Box2DPrismaticJoint::setEnableMotor(bool enableMotor)
{
    if (mPrismaticJointDef.enableMotor == enableMotor)
        return;

    mPrismaticJointDef.enableMotor = enableMotor;
    if (prismaticJoint())
        prismaticJoint()->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

QPointF Box2DPrismaticJoint::axis() const
{
    return world()->toPixels(mPrismaticJointDef.localAxisA);
}

void Box2DPrismaticJoint::setAxis(const QPointF &axis)
{
    mPrismaticJointDef.localAxisA = invertY(axis);
    mPrismaticJointDef.localAxisA.Normalize();
    emit axisChanged();
}

QPointF Box2DPrismaticJoint::localAnchorA() const
{
    return world()->toPixels(mPrismaticJointDef.localAnchorA);
}

QPointF Box2DPrismaticJoint::localAnchorB() const
{
    return world()->toPixels(mPrismaticJointDef.localAnchorB);
}

void Box2DPrismaticJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mPrismaticJointDef.localAnchorA = world()->toMeters(localAnchorA);
    mAnchorsAuto = false;
    emit localAnchorAChanged();
}

void Box2DPrismaticJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mPrismaticJointDef.localAnchorB = world()->toMeters(localAnchorB);
    mAnchorsAuto = false;
    emit localAnchorBChanged();
}

b2Joint *Box2DPrismaticJoint::createJoint()
{
    if (mAnchorsAuto) {
        mPrismaticJointDef.Initialize(mPrismaticJointDef.bodyA,
                                      mPrismaticJointDef.bodyB,
                                      mPrismaticJointDef.bodyA->GetWorldCenter(),
                                      mPrismaticJointDef.localAxisA);
    } else {
        mPrismaticJointDef.referenceAngle = 0.0;
    }

    return world()->world().CreateJoint(&mPrismaticJointDef);
}

float Box2DPrismaticJoint::getJointTranslation() const
{
    if (prismaticJoint())
        return world()->toPixels(prismaticJoint()->GetJointTranslation());
    return 0.0;
}

float Box2DPrismaticJoint::getJointSpeed() const
{
    if (prismaticJoint())
        return prismaticJoint()->GetJointSpeed();
    return 0.0;
}
