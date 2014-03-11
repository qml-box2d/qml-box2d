/*
 * box2dmousejoint.cpp
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

#include "box2dmousejoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DMouseJoint::Box2DMouseJoint(QObject *parent) :
    Box2DJoint(parent),
    mMouseJointDef(),
    mMouseJoint(0)
{
}

Box2DMouseJoint::~Box2DMouseJoint()
{
    cleanup(world());
}

float Box2DMouseJoint::dampingRatio() const
{
    if(mMouseJoint) return mMouseJoint->GetDampingRatio();
    return mMouseJointDef.dampingRatio;
}

void Box2DMouseJoint::setDampingRatio(float dampingRatio)
{
    mMouseJointDef.dampingRatio = dampingRatio;
    if(mMouseJoint) mMouseJoint->SetDampingRatio(dampingRatio);

}

float Box2DMouseJoint::frequencyHz() const
{
    if(mMouseJoint) return mMouseJoint->GetFrequency();
    return mMouseJointDef.frequencyHz;
}

void Box2DMouseJoint::setFrequencyHz(float frequencyHz)
{
    mMouseJointDef.frequencyHz = frequencyHz;
    if(mMouseJoint) mMouseJoint->SetFrequency(frequencyHz);
}

float Box2DMouseJoint::maxForce() const
{
    if(mMouseJoint) return mMouseJoint->GetMaxForce();
    return mMouseJointDef.maxForce;
}

void Box2DMouseJoint::setMaxForce(float maxForce)
{
    mMouseJointDef.maxForce = maxForce;
    if(mMouseJoint) mMouseJoint->SetMaxForce(maxForce);
}

QPointF Box2DMouseJoint::target() const
{
    b2Vec2 point;
    if(mMouseJoint) point = mMouseJoint->GetTarget();
    else point = mMouseJointDef.target;
    return QPointF(point.x * scaleRatio,-point.y * scaleRatio);
}

void Box2DMouseJoint::setTarget(const QPointF &_target)
{
    if(_target == target()) return;
    mMouseJointDef.target = b2Vec2(_target.x() / scaleRatio, -_target.y() / scaleRatio);
    if(mMouseJoint) mMouseJoint->SetTarget(mMouseJointDef.target);
}

void Box2DMouseJoint::nullifyJoint()
{
    mMouseJoint = 0;
}

void Box2DMouseJoint::createJoint()
{    
    mMouseJointDef.bodyA = bodyA()->body();
    mMouseJointDef.bodyB = bodyB()->body();

    mMouseJoint = static_cast<b2MouseJoint*>
            (world()->CreateJoint(&mMouseJointDef));
    mMouseJoint->SetUserData(this);
    mInitializePending = false;
    emit created();
}

void Box2DMouseJoint::cleanup(b2World *world)
{
    if(!world) {
        qWarning() << "MouseJoint: There is no world connected";
        return;
    }
    if (mMouseJoint && bodyA() && bodyB()) {
        mMouseJoint->SetUserData(0);
        world->DestroyJoint(mMouseJoint);
        mMouseJoint = 0;
    }
}

b2Joint *Box2DMouseJoint::GetJoint()
{
    return mMouseJoint;
}

QPointF Box2DMouseJoint::GetReactionForce(float32 inv_dt) const
{
    if(mMouseJoint)
    {
        b2Vec2 point = mMouseJoint->GetReactionForce(inv_dt);
        return QPointF(point.x * scaleRatio,point.y * scaleRatio);
    }
    return QPointF();
}

float Box2DMouseJoint::GetReactionTorque(float32 inv_dt) const
{
    if(mMouseJoint) return mMouseJoint->GetReactionTorque(inv_dt);
    return 0.0f;
}
