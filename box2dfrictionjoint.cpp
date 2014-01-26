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

#include "box2dfrictionjoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DFrictionJoint::Box2DFrictionJoint(QObject *parent) :
    Box2DJoint(parent),
    mFrictionJointDef(),
    mFrictionJoint(0),
    anchorsAuto(true)
{
}

Box2DFrictionJoint::~Box2DFrictionJoint()
{
    cleanup(world());
}

float Box2DFrictionJoint::maxForce() const
{
    if(mFrictionJoint) return mFrictionJoint->GetMaxForce();
    return mFrictionJointDef.maxForce;
}

void Box2DFrictionJoint::setMaxForce(float maxForce)
{
    if(mFrictionJoint && mFrictionJoint->GetMaxForce() == maxForce) return;
    if(mFrictionJoint) mFrictionJoint->SetMaxForce(maxForce);
    else mFrictionJointDef.maxForce = maxForce;
    emit maxForceChanged();
}

float Box2DFrictionJoint::maxTorque() const
{
    if(mFrictionJoint) return mFrictionJoint->GetMaxTorque();
    return mFrictionJointDef.maxTorque;
}

void Box2DFrictionJoint::setMaxTorque(float maxTorque)
{
    if(mFrictionJoint && mFrictionJoint->GetMaxTorque() == maxTorque) return;
    if(mFrictionJoint) mFrictionJoint->SetMaxForce(maxTorque);
    else mFrictionJointDef.maxTorque = maxTorque;
    emit maxTorqueChanged();
}

QPointF Box2DFrictionJoint::localAnchorA() const
{
    if(mFrictionJoint) QPointF(mFrictionJoint->GetAnchorA().x * scaleRatio,
                               -mFrictionJoint->GetAnchorA().y * scaleRatio);
    return QPointF(mFrictionJointDef.localAnchorA.x * scaleRatio,
                   mFrictionJointDef.localAnchorA.y * scaleRatio);
}

void Box2DFrictionJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mFrictionJointDef.localAnchorA = b2Vec2(localAnchorA.x() / scaleRatio
                                            ,-localAnchorA.y() / scaleRatio);
    anchorsAuto = true;
    emit localAnchorAChanged();
}

QPointF Box2DFrictionJoint::localAnchorB() const
{
    if(mFrictionJoint) QPointF(mFrictionJoint->GetAnchorB().x * scaleRatio,
                               -mFrictionJoint->GetAnchorB().y * scaleRatio);
    return QPointF(mFrictionJointDef.localAnchorB.x * scaleRatio,
                   mFrictionJointDef.localAnchorB.y * scaleRatio);
}

void Box2DFrictionJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mFrictionJointDef.localAnchorB = b2Vec2(localAnchorB.x() / scaleRatio,
                                            -localAnchorB.y() / scaleRatio);
    anchorsAuto = true;
    emit localAnchorBChanged();
}

void Box2DFrictionJoint::nullifyJoint()
{
    mFrictionJoint = 0;
}

void Box2DFrictionJoint::createJoint()
{
    if(anchorsAuto)
    {
        mFrictionJointDef.bodyA = bodyA()->body();
        mFrictionJointDef.bodyB = bodyB()->body();
    }
    else
        mFrictionJointDef.Initialize(bodyA()->body(),
                                     bodyB()->body(),
                                     bodyA()->body()->GetWorldCenter());
    mFrictionJointDef.collideConnected = collideConnected();
    mFrictionJoint = static_cast<b2FrictionJoint *>(world()->CreateJoint(&mFrictionJointDef));
    mFrictionJoint->SetUserData(this);
    mInitializePending = false;
    emit created();
}

void Box2DFrictionJoint::cleanup(b2World *world)
{
    if(!world) {
        qWarning() << "FrictionJoint: There is no world connected";
        return;
    }
    if (mFrictionJoint && bodyA() && bodyB()) {
        mFrictionJoint->SetUserData(0);
        world->DestroyJoint(mFrictionJoint);
        mFrictionJoint = 0;
    }
}

b2Joint *Box2DFrictionJoint::GetJoint()
{
    return mFrictionJoint;
}

QPointF Box2DFrictionJoint::GetReactionForce(float32 inv_dt) const
{
    if(mFrictionJoint)
    {
        b2Vec2 point = mFrictionJoint->GetReactionForce(inv_dt);
        return QPointF(point.x * scaleRatio,point.y * scaleRatio);
    }
    return QPointF();
}

float Box2DFrictionJoint::GetReactionTorque(float32 inv_dt) const
{
    if(mFrictionJoint) return mFrictionJoint->GetReactionTorque(inv_dt);
    return 0.0f;
}

