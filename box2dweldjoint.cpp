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
    Box2DJoint(mWeldJointDef, parent),
    mAnchorsAuto(true)
{
}

void Box2DWeldJoint::setReferenceAngle(float referenceAngle)
{
    float referenceAngleRad = referenceAngle * b2_pi / -180;
    if (mWeldJointDef.referenceAngle == referenceAngleRad)
        return;

    mWeldJointDef.referenceAngle = referenceAngleRad;
    emit referenceAngleChanged();
}

void Box2DWeldJoint::setFrequencyHz(float frequencyHz)
{
    if (mWeldJointDef.frequencyHz == frequencyHz)
        return;

    mWeldJointDef.frequencyHz = frequencyHz;
    if (weldJoint())
        weldJoint()->SetFrequency(frequencyHz);
    emit frequencyHzChanged();
}

void Box2DWeldJoint::setDampingRatio(float dampingRatio)
{
    if (mWeldJointDef.dampingRatio == dampingRatio)
        return;

    mWeldJointDef.dampingRatio = dampingRatio;
    if (weldJoint())
        weldJoint()->SetDampingRatio(dampingRatio);
    emit dampingRatioChanged();
}

QPointF Box2DWeldJoint::localAnchorA() const
{
    return QPointF(mWeldJointDef.localAnchorA.x * scaleRatio,
                   -mWeldJointDef.localAnchorA.y * scaleRatio);
}

void Box2DWeldJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mWeldJointDef.localAnchorA = b2Vec2(localAnchorA.x() / scaleRatio,
                                        -localAnchorA.y() / scaleRatio);
    mAnchorsAuto = false;
    emit localAnchorAChanged();
}

QPointF Box2DWeldJoint::localAnchorB() const
{
        return QPointF(mWeldJointDef.localAnchorB.x * scaleRatio,
                       -mWeldJointDef.localAnchorB.y * scaleRatio);
}

void Box2DWeldJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mWeldJointDef.localAnchorB = b2Vec2(localAnchorB.x() / scaleRatio,
                                        -localAnchorB.y() / scaleRatio);
    mAnchorsAuto = false;
    emit localAnchorBChanged();
}

b2Joint *Box2DWeldJoint::createJoint()
{
    if (mAnchorsAuto) {
        mWeldJointDef.Initialize(bodyA()->body(),
                                 bodyB()->body(),
                                 bodyA()->body()->GetWorldCenter());
    } else {
        mWeldJointDef.bodyA = bodyA()->body();
        mWeldJointDef.bodyB = bodyB()->body();
    }

    return world()->CreateJoint(&mWeldJointDef);
}
