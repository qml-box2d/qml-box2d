/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the Box2D QML plugin.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library;  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2ddistancejoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DDistanceJoint::Box2DDistanceJoint(QObject *parent) :
    Box2DJoint(parent),
    mDistanceJointDef(),
    mDistanceJoint(0),
    mOverrideAnchorLength(false),
    mLength(0),
    mOverrideLocalAnchorA(false),
    mOverrideLocalAnchorB(false)
{
}

Box2DDistanceJoint::~Box2DDistanceJoint()
{
    cleanup(world());
}

float Box2DDistanceJoint::length() const
{
    return mOverrideAnchorLength ? mLength : mDistanceJointDef.length;
}

void Box2DDistanceJoint::setLength(float length)
{
    if (mLength == length / scaleRatio)
        return;

    mOverrideAnchorLength = true;
    mLength = length / scaleRatio;

    if (mDistanceJoint)
        mDistanceJoint->SetLength(length / scaleRatio);
    emit lengthChanged();
}

float Box2DDistanceJoint::frequencyHz() const
{
    return mDistanceJointDef.frequencyHz;
}

void Box2DDistanceJoint::setFrequencyHz(float frequencyHz)
{
    if (mDistanceJointDef.frequencyHz == frequencyHz)
        return;

    mDistanceJointDef.frequencyHz = frequencyHz;
    if (mDistanceJoint)
        mDistanceJoint->SetFrequency(frequencyHz);
    emit frequencyHzChanged();
}

float Box2DDistanceJoint::dampingRatio() const
{
    return mDistanceJointDef.dampingRatio;
}

void Box2DDistanceJoint::setDampingRatio(float dampingRatio)
{
    if (mDistanceJointDef.dampingRatio == dampingRatio)
        return;

    mDistanceJointDef.dampingRatio = dampingRatio;
    if (mDistanceJoint)
        mDistanceJoint->SetDampingRatio(dampingRatio);
    emit dampingRatioChanged();
}

QPointF Box2DDistanceJoint::localAnchorA() const
{
    if (mOverrideLocalAnchorA)
        return mLocalAnchorA;
    else
        return QPointF(mDistanceJointDef.localAnchorA.x * scaleRatio,
                       -mDistanceJointDef.localAnchorA.y * scaleRatio);
}

void Box2DDistanceJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    if (mOverrideLocalAnchorA && mLocalAnchorA == localAnchorA)
        return;

    mOverrideLocalAnchorA = true;
    mLocalAnchorA = localAnchorA;

    emit localAnchorAChanged();
}

QPointF Box2DDistanceJoint::localAnchorB() const
{
    if (mOverrideLocalAnchorB)
        return mLocalAnchorB;
    else
        return QPointF(mDistanceJointDef.localAnchorB.x * scaleRatio,
                       -mDistanceJointDef.localAnchorB.y * scaleRatio);
}

void Box2DDistanceJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    if (mOverrideLocalAnchorB && mLocalAnchorB == localAnchorB)
        return;

    mOverrideLocalAnchorB = true;
    mLocalAnchorB = localAnchorB;

    emit localAnchorBChanged();
}

void Box2DDistanceJoint::nullifyJoint()
{
    mDistanceJoint = 0;
}

void Box2DDistanceJoint::createJoint()
{
    b2Vec2 anchorA = mOverrideLocalAnchorA ?
                b2Vec2(mLocalAnchorA.x() / scaleRatio,
                       -mLocalAnchorA.y() / scaleRatio) +
                bodyA()->body()->GetPosition() :
                bodyA()->body()->GetWorldCenter();

    b2Vec2 anchorB = mOverrideLocalAnchorB ?
                b2Vec2(mLocalAnchorB.x() / scaleRatio,
                       -mLocalAnchorB.y() / scaleRatio) +
                bodyB()->body()->GetPosition() :
                bodyB()->body()->GetWorldCenter();

    mDistanceJointDef.Initialize(bodyA()->body(), bodyB()->body(),
                                 anchorA, anchorB);
    mDistanceJointDef.collideConnected = collideConnected();
    if (mOverrideAnchorLength)
        mDistanceJointDef.length = mLength;
    mDistanceJoint = static_cast<b2DistanceJoint*>
            (world()->CreateJoint(&mDistanceJointDef));
    mDistanceJoint->SetUserData(this);
    mInitializePending = false;
}

void Box2DDistanceJoint::cleanup(b2World *world)
{
    if (mDistanceJoint && bodyA() && bodyB()) {
        mDistanceJoint->SetUserData(0);
        world->DestroyJoint(mDistanceJoint);
        mDistanceJoint = 0;
    }
}
