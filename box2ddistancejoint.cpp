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
    anchorsAuto(true)
{
}

float Box2DDistanceJoint::length() const
{
    if (distanceJoint())
        return distanceJoint()->GetLength();
    return mDistanceJointDef.length;
}

void Box2DDistanceJoint::setLength(float _length)
{
    if (qFuzzyCompare(length(), _length / scaleRatio))
        return;
    mDistanceJointDef.length = _length / scaleRatio;
    if (distanceJoint())
        distanceJoint()->SetLength(mDistanceJointDef.length);
    emit lengthChanged();
}

float Box2DDistanceJoint::frequencyHz() const
{
    if (distanceJoint())
        return distanceJoint()->GetFrequency();
    return mDistanceJointDef.frequencyHz;
}

void Box2DDistanceJoint::setFrequencyHz(float _frequencyHz)
{
    if (frequencyHz() == _frequencyHz)
        return;
    mDistanceJointDef.frequencyHz = _frequencyHz;
    if (distanceJoint())
        distanceJoint()->SetFrequency(_frequencyHz);
    emit frequencyHzChanged();
}

float Box2DDistanceJoint::dampingRatio() const
{
    if (distanceJoint())
        return distanceJoint()->GetDampingRatio();
    return mDistanceJointDef.dampingRatio;
}

void Box2DDistanceJoint::setDampingRatio(float _dampingRatio)
{
    if (dampingRatio() == _dampingRatio)
        return;

    mDistanceJointDef.dampingRatio = _dampingRatio;
    if (distanceJoint())
        distanceJoint()->SetDampingRatio(_dampingRatio);
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

b2Joint *Box2DDistanceJoint::createJoint()
{
    if (anchorsAuto) {
        mDistanceJointDef.Initialize(bodyA()->body(),
                                     bodyB()->body(),
                                     bodyA()->body()->GetWorldCenter(),
                                     bodyB()->body()->GetWorldCenter());
    } else {
        mDistanceJointDef.bodyA = bodyA()->body();
        mDistanceJointDef.bodyB = bodyB()->body();
    }

    mDistanceJointDef.collideConnected = collideConnected();

    return world()->CreateJoint(&mDistanceJointDef);
}

QPointF Box2DDistanceJoint::getReactionForce(float32 inv_dt) const
{
    if (distanceJoint()) {
        b2Vec2 point = distanceJoint()->GetReactionForce(inv_dt);
        return QPointF(point.x * scaleRatio, point.y * scaleRatio);
    }
    return QPointF();
}

float Box2DDistanceJoint::getReactionTorque(float32 inv_dt) const
{
    if (distanceJoint())
        return distanceJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
