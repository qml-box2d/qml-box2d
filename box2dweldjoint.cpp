/*
 * box2dweldjoint.cpp
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

#include "box2dweldjoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DWeldJoint::Box2DWeldJoint(QObject *parent) :
    Box2DJoint(parent),
    mWeldJointDef(),
    mWeldJoint(0),
    anchorsAuto(true)
{
}

Box2DWeldJoint::~Box2DWeldJoint()
{
    cleanup(world());
}

float Box2DWeldJoint::referenceAngle() const
{
    return mWeldJointDef.referenceAngle;
}

void Box2DWeldJoint::setReferenceAngle(float referenceAngle)
{
    float referenceAngleRad = referenceAngle * b2_pi / -180;
    if (qFuzzyCompare(mWeldJointDef.referenceAngle,referenceAngleRad))
        return;
    mWeldJointDef.referenceAngle = referenceAngleRad;
    emit referenceAngleChanged();
}

float Box2DWeldJoint::frequencyHz() const
{
    return mWeldJointDef.frequencyHz;
}

void Box2DWeldJoint::setFrequencyHz(float frequencyHz)
{
    if (qFuzzyCompare(mWeldJointDef.frequencyHz,frequencyHz))
        return;

    mWeldJointDef.frequencyHz = frequencyHz;
    if (mWeldJoint)
        mWeldJoint->SetFrequency(frequencyHz);
    emit frequencyHzChanged();
}

float Box2DWeldJoint::dampingRatio() const
{
    return mWeldJointDef.dampingRatio;
}

void Box2DWeldJoint::setDampingRatio(float dampingRatio)
{
    if (qFuzzyCompare(mWeldJointDef.dampingRatio,dampingRatio))
        return;

    mWeldJointDef.dampingRatio = dampingRatio;
    if (mWeldJoint)
        mWeldJoint->SetDampingRatio(dampingRatio);
    emit dampingRatioChanged();
}

QPointF Box2DWeldJoint::localAnchorA() const
{
    return QPointF(mWeldJointDef.localAnchorA.x * scaleRatio,
                       -mWeldJointDef.localAnchorA.y * scaleRatio);
}

void Box2DWeldJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mWeldJointDef.localAnchorA = b2Vec2(localAnchorA.x() / scaleRatio,-localAnchorA.y() / scaleRatio);
    anchorsAuto = false;
    emit localAnchorAChanged();
}

QPointF Box2DWeldJoint::localAnchorB() const
{
        return QPointF(mWeldJointDef.localAnchorB.x * scaleRatio,
                       -mWeldJointDef.localAnchorB.y * scaleRatio);
}

void Box2DWeldJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mWeldJointDef.localAnchorB = b2Vec2(localAnchorB.x() / scaleRatio,-localAnchorB.y() / scaleRatio);
    anchorsAuto = false;
    emit localAnchorBChanged();
}

void Box2DWeldJoint::nullifyJoint()
{
    mWeldJoint = 0;
}

void Box2DWeldJoint::createJoint()
{
    if(anchorsAuto)
        mWeldJointDef.Initialize(bodyA()->body(), bodyB()->body(),bodyA()->body()->GetWorldCenter());
    else
    {
        mWeldJointDef.bodyA = bodyA()->body();
        mWeldJointDef.bodyB = bodyB()->body();
    }
    mWeldJointDef.collideConnected = collideConnected();
    mWeldJoint = static_cast<b2WeldJoint*>
            (world()->CreateJoint(&mWeldJointDef));

    mWeldJoint->SetUserData(this);
    mInitializePending = false;
    emit created();
}

void Box2DWeldJoint::cleanup(b2World *world)
{
    if(!world) {
        qWarning() << "WeldJoint: There is no world connected";
        return;
    }
    if (mWeldJoint && bodyA() && bodyB()) {
        mWeldJoint->SetUserData(0);
        world->DestroyJoint(mWeldJoint);
        mWeldJoint = 0;
    }
}

b2Joint *Box2DWeldJoint::GetJoint()
{
    return mWeldJoint;
}
