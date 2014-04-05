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

#include "box2dpulleyjoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DPulleyJoint::Box2DPulleyJoint(QObject *parent) :
    Box2DJoint(parent)
{
}

float Box2DPulleyJoint::lengthA() const
{
    if (pulleyJoint())
        return pulleyJoint()->GetLengthA() * scaleRatio;
    return mPulleyJointDef.lengthA * scaleRatio;
}

void Box2DPulleyJoint::setLengthA(float lengthA)
{
    if (mPulleyJointDef.lengthA * scaleRatio == lengthA)
        return;
    mPulleyJointDef.lengthA = lengthA / scaleRatio;
    emit lengthAChanged();
}

float Box2DPulleyJoint::lengthB() const
{
    if (pulleyJoint())
        return pulleyJoint()->GetLengthB() * scaleRatio;
    return mPulleyJointDef.lengthB * scaleRatio;
}

void Box2DPulleyJoint::setLengthB(float lengthB)
{
    if (mPulleyJointDef.lengthB * scaleRatio == lengthB)
        return;
    mPulleyJointDef.lengthB = lengthB / scaleRatio;
    emit lengthBChanged();
}

float Box2DPulleyJoint::ratio() const
{
    if (pulleyJoint())
        return pulleyJoint()->GetRatio();
    return mPulleyJointDef.ratio;
}

void Box2DPulleyJoint::setRatio(float ratio)
{
    if (mPulleyJointDef.ratio == ratio)
        return;
    mPulleyJointDef.ratio = ratio;
    emit ratioChanged();
}

QPointF Box2DPulleyJoint::groundAnchorA() const
{
    if (pulleyJoint())
        return QPointF(pulleyJoint()->GetGroundAnchorA().x * scaleRatio,
                       -pulleyJoint()->GetGroundAnchorA().y * scaleRatio);
    return QPointF(mPulleyJointDef.groundAnchorA.x * scaleRatio,
                   -mPulleyJointDef.groundAnchorA.y * scaleRatio);
}

void Box2DPulleyJoint::setGroundAnchorA(const QPointF &groundAnchorA)
{
    mPulleyJointDef.groundAnchorA = b2Vec2(groundAnchorA.x() / scaleRatio,
                                           -groundAnchorA.y() / scaleRatio);
    emit groundAnchorAChanged();
}

QPointF Box2DPulleyJoint::groundAnchorB() const
{
    if (pulleyJoint())
        return QPointF(pulleyJoint()->GetGroundAnchorB().x * scaleRatio,
                       -pulleyJoint()->GetGroundAnchorB().y * scaleRatio);
    return QPointF(mPulleyJointDef.groundAnchorB.x * scaleRatio,
                   -mPulleyJointDef.groundAnchorB.y * scaleRatio);
}

void Box2DPulleyJoint::setGroundAnchorB(const QPointF &groundAnchorB)
{
    mPulleyJointDef.groundAnchorB = b2Vec2(groundAnchorB.x() / scaleRatio,
                                           -groundAnchorB.y() / scaleRatio);
    emit groundAnchorBChanged();
}

QPointF Box2DPulleyJoint::localAnchorA() const
{
    if (pulleyJoint())
        return QPointF(pulleyJoint()->GetAnchorA().x * scaleRatio,
                       -pulleyJoint()->GetAnchorA().y * scaleRatio);
    return QPointF(mPulleyJointDef.localAnchorA.x * scaleRatio,
                   -mPulleyJointDef.localAnchorA.y * scaleRatio);
}

void Box2DPulleyJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mPulleyJointDef.localAnchorA = b2Vec2(localAnchorA.x() / scaleRatio,
                                          -localAnchorA.y() / scaleRatio);
    emit localAnchorAChanged();
}

QPointF Box2DPulleyJoint::localAnchorB() const
{
    if (pulleyJoint())
        return QPointF(pulleyJoint()->GetAnchorB().x * scaleRatio,
                       -pulleyJoint()->GetAnchorB().y * scaleRatio);
    return QPointF(mPulleyJointDef.localAnchorB.x * scaleRatio,
                   mPulleyJointDef.localAnchorB.y * scaleRatio);
}

void Box2DPulleyJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mPulleyJointDef.localAnchorB = b2Vec2(localAnchorB.x() / scaleRatio,
                                          -localAnchorB.y() / scaleRatio);
    emit localAnchorBChanged();
}

b2Joint *Box2DPulleyJoint::createJoint()
{
    if (qFuzzyIsNull(mPulleyJointDef.lengthA) || qFuzzyIsNull(mPulleyJointDef.lengthB)) {
        qWarning() << "PulleyJoint: the joint length cannot be zero";
        return 0;
    }
    mPulleyJointDef.bodyA = bodyA()->body();
    mPulleyJointDef.bodyB = bodyB()->body();
    mPulleyJointDef.collideConnected = collideConnected();
    return world()->CreateJoint(&mPulleyJointDef);
}

float Box2DPulleyJoint::getCurrentLengthA() const
{
    if (pulleyJoint())
        return pulleyJoint()->GetCurrentLengthA() * scaleRatio;
    return 0.0f;
}

float Box2DPulleyJoint::getCurrentLengthB() const
{
    if (pulleyJoint())
        return pulleyJoint()->GetCurrentLengthB() * scaleRatio;
    return 0.0f;
}

QPointF Box2DPulleyJoint::getReactionForce(float32 inv_dt) const
{
    if (pulleyJoint()) {
        b2Vec2 point = pulleyJoint()->GetReactionForce(inv_dt);
        return QPointF(point.x * scaleRatio,point.y * scaleRatio);
    }
    return QPointF();
}

float Box2DPulleyJoint::getReactionTorque(float32 inv_dt) const
{
    if (pulleyJoint())
        return pulleyJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
