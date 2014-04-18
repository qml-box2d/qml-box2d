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
    Box2DJoint(mDistanceJointDef, parent),
    mAnchorsAuto(true)
{
}

float Box2DDistanceJoint::length() const
{
    return world()->toPixels(mDistanceJointDef.length);
}

void Box2DDistanceJoint::setLength(float length)
{
    if (mDistanceJointDef.length == world()->toMeters(length))
        return;

    mDistanceJointDef.length = world()->toMeters(length);
    if (distanceJoint())
        distanceJoint()->SetLength(mDistanceJointDef.length);
    emit lengthChanged();
}

void Box2DDistanceJoint::setFrequencyHz(float frequencyHz)
{
    if (mDistanceJointDef.frequencyHz == frequencyHz)
        return;

    mDistanceJointDef.frequencyHz = frequencyHz;
    if (distanceJoint())
        distanceJoint()->SetFrequency(frequencyHz);
    emit frequencyHzChanged();
}

void Box2DDistanceJoint::setDampingRatio(float dampingRatio)
{
    if (mDistanceJointDef.dampingRatio == dampingRatio)
        return;

    mDistanceJointDef.dampingRatio = dampingRatio;
    if (distanceJoint())
        distanceJoint()->SetDampingRatio(dampingRatio);
    emit dampingRatioChanged();
}

QPointF Box2DDistanceJoint::localAnchorA() const
{
    return world()->toPixels(mDistanceJointDef.localAnchorA);
}

void Box2DDistanceJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mDistanceJointDef.localAnchorA = world()->toMeters(localAnchorA);
    mAnchorsAuto = false;
    emit localAnchorBChanged();
}

QPointF Box2DDistanceJoint::localAnchorB() const
{
    return world()->toPixels(mDistanceJointDef.localAnchorB);
}

void Box2DDistanceJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mDistanceJointDef.localAnchorB = world()->toMeters(localAnchorB);
    mAnchorsAuto = false;
    emit localAnchorBChanged();
}

b2Joint *Box2DDistanceJoint::createJoint()
{
    if (mAnchorsAuto) {
        mDistanceJointDef.Initialize(mDistanceJointDef.bodyA,
                                     mDistanceJointDef.bodyB,
                                     mDistanceJointDef.bodyA->GetWorldCenter(),
                                     mDistanceJointDef.bodyB->GetWorldCenter());
    }

    return world()->world().CreateJoint(&mDistanceJointDef);
}

QPointF Box2DDistanceJoint::getReactionForce(float32 inv_dt) const
{
    if (distanceJoint())
        return invertY(distanceJoint()->GetReactionForce(inv_dt));
    return QPointF();
}

float Box2DDistanceJoint::getReactionTorque(float32 inv_dt) const
{
    if (distanceJoint())
        return distanceJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
