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
    Box2DJoint(mPulleyJointDef, parent)
{
}

float Box2DPulleyJoint::lengthA() const
{
    return world()->toPixels(mPulleyJointDef.lengthA);
}

void Box2DPulleyJoint::setLengthA(float lengthA)
{
    if (mPulleyJointDef.lengthA == world()->toMeters(lengthA))
        return;

    mPulleyJointDef.lengthA = world()->toMeters(lengthA);
    emit lengthAChanged();
}

float Box2DPulleyJoint::lengthB() const
{
    return world()->toPixels(mPulleyJointDef.lengthB);
}

void Box2DPulleyJoint::setLengthB(float lengthB)
{
    if (mPulleyJointDef.lengthB == world()->toMeters(lengthB))
        return;

    mPulleyJointDef.lengthB = world()->toMeters(lengthB);
    emit lengthBChanged();
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
    return world()->toPixels(mPulleyJointDef.groundAnchorA);
}

void Box2DPulleyJoint::setGroundAnchorA(const QPointF &groundAnchorA)
{
    mPulleyJointDef.groundAnchorA = world()->toMeters(groundAnchorA);
    emit groundAnchorAChanged();
}

QPointF Box2DPulleyJoint::groundAnchorB() const
{
    return world()->toPixels(mPulleyJointDef.groundAnchorB);
}

void Box2DPulleyJoint::setGroundAnchorB(const QPointF &groundAnchorB)
{
    mPulleyJointDef.groundAnchorB = world()->toMeters(groundAnchorB);
    emit groundAnchorBChanged();
}

QPointF Box2DPulleyJoint::localAnchorA() const
{
    if (pulleyJoint())
        return world()->toPixels(pulleyJoint()->GetAnchorA());
    return world()->toPixels(mPulleyJointDef.localAnchorA);
}

void Box2DPulleyJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mPulleyJointDef.localAnchorA = world()->toMeters(localAnchorA);
    emit localAnchorAChanged();
}

QPointF Box2DPulleyJoint::localAnchorB() const
{
    if (pulleyJoint())
        return world()->toPixels(pulleyJoint()->GetAnchorB());
    return world()->toPixels(mPulleyJointDef.localAnchorB);
}

void Box2DPulleyJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mPulleyJointDef.localAnchorB = world()->toMeters(localAnchorB);
    emit localAnchorBChanged();
}

b2Joint *Box2DPulleyJoint::createJoint()
{
    if (qFuzzyIsNull(mPulleyJointDef.lengthA) || qFuzzyIsNull(mPulleyJointDef.lengthB)) {
        qWarning() << "PulleyJoint: the joint length cannot be zero";
        return 0;
    }

    return world()->world().CreateJoint(&mPulleyJointDef);
}

float Box2DPulleyJoint::getCurrentLengthA() const
{
    if (pulleyJoint())
        return world()->toPixels(pulleyJoint()->GetCurrentLengthA());
    return lengthA();
}

float Box2DPulleyJoint::getCurrentLengthB() const
{
    if (pulleyJoint())
        return world()->toPixels(pulleyJoint()->GetCurrentLengthB());
    return lengthB();
}

QPointF Box2DPulleyJoint::getReactionForce(float32 inv_dt) const
{
    if (pulleyJoint())
        return invertY(pulleyJoint()->GetReactionForce(inv_dt));
    return QPointF();
}

float Box2DPulleyJoint::getReactionTorque(float32 inv_dt) const
{
    if (pulleyJoint())
        return pulleyJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
