/*
 * box2ddistancejoint.cpp
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

#include "box2ddistancejoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DDistanceJoint::Box2DDistanceJoint(QObject *parent) :
    Box2DJoint(parent),
    mDistanceJointDef(),
    mDistanceJoint(0),
    anchorsAuto(true)
{
}

Box2DDistanceJoint::~Box2DDistanceJoint()
{
    cleanup(world());
}

float Box2DDistanceJoint::length() const
{
    if(mDistanceJoint) return mDistanceJoint->GetLength();
    return mDistanceJointDef.length;
}

void Box2DDistanceJoint::setLength(float _length)
{
    if (qFuzzyCompare(length(),_length / scaleRatio))
        return;
    mDistanceJointDef.length = _length / scaleRatio;
    if (mDistanceJoint)
        mDistanceJoint->SetLength(mDistanceJointDef.length);
    emit lengthChanged();
}

float Box2DDistanceJoint::frequencyHz() const
{
    if(mDistanceJoint) return mDistanceJoint->GetFrequency();
    return mDistanceJointDef.frequencyHz;
}

void Box2DDistanceJoint::setFrequencyHz(float _frequencyHz)
{
    if (frequencyHz() == _frequencyHz)
        return;
    mDistanceJointDef.frequencyHz = _frequencyHz;
    if (mDistanceJoint)
        mDistanceJoint->SetFrequency(_frequencyHz);
    emit frequencyHzChanged();
}

float Box2DDistanceJoint::dampingRatio() const
{
    if(mDistanceJoint) mDistanceJoint->GetDampingRatio();
    return mDistanceJointDef.dampingRatio;
}

void Box2DDistanceJoint::setDampingRatio(float _dampingRatio)
{
    if (dampingRatio() == _dampingRatio)
        return;

    mDistanceJointDef.dampingRatio = _dampingRatio;
    if (mDistanceJoint)
        mDistanceJoint->SetDampingRatio(_dampingRatio);
    emit dampingRatioChanged();
}

QPointF Box2DDistanceJoint::localAnchorA() const
{
    return QPointF(mDistanceJointDef.localAnchorA.x * scaleRatio,
                       -mDistanceJointDef.localAnchorA.y * scaleRatio);
}

void Box2DDistanceJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mDistanceJointDef.localAnchorA = b2Vec2(localAnchorA.x() / scaleRatio,
                                         -localAnchorA.y() / scaleRatio);
    anchorsAuto = false;
    emit localAnchorBChanged();
}

QPointF Box2DDistanceJoint::localAnchorB() const
{
    return QPointF(mDistanceJointDef.localAnchorB.x * scaleRatio,
                       -mDistanceJointDef.localAnchorB.y * scaleRatio);
}

void Box2DDistanceJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mDistanceJointDef.localAnchorB = b2Vec2(localAnchorB.x() / scaleRatio,
                                         -localAnchorB.y() / scaleRatio);
    anchorsAuto = false;
    emit localAnchorBChanged();
}

void Box2DDistanceJoint::nullifyJoint()
{
    mDistanceJoint = 0;
}

void Box2DDistanceJoint::createJoint()
{
    if(anchorsAuto) mDistanceJointDef.Initialize(bodyA()->body(),
                                 bodyB()->body(),
                                 bodyA()->body()->GetWorldCenter(),
                                 bodyB()->body()->GetWorldCenter());
    else {
        mDistanceJointDef.bodyA = bodyA()->body();
        mDistanceJointDef.bodyB = bodyB()->body();
    }

    mDistanceJointDef.collideConnected = collideConnected();
    mDistanceJoint = static_cast<b2DistanceJoint*>
            (world()->CreateJoint(&mDistanceJointDef));
    mDistanceJoint->SetUserData(this);
    mInitializePending = false;
    emit created();
}

void Box2DDistanceJoint::cleanup(b2World *world)
{
    if(!world) {
        qWarning() << "DistanceJoint: There is no world connected";
        return;
    }
    if (mDistanceJoint && bodyA() && bodyB()) {
        mDistanceJoint->SetUserData(0);
        world->DestroyJoint(mDistanceJoint);
        mDistanceJoint = 0;
    }
}

b2Joint *Box2DDistanceJoint::GetJoint()
{
    return mDistanceJoint;
}

QPointF Box2DDistanceJoint::GetReactionForce(float32 inv_dt) const
{
    if(mDistanceJoint)
    {
        b2Vec2 point = mDistanceJoint->GetReactionForce(inv_dt);
        return QPointF(point.x * scaleRatio,point.y * scaleRatio);
    }
    return QPointF();
}

float Box2DDistanceJoint::GetReactionTorque(float32 inv_dt) const
{
    if(mDistanceJoint) return mDistanceJoint->GetReactionTorque(inv_dt);
    return 0.0f;
}
