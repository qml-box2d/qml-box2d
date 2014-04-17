/*
 * box2drevolutejoint.cpp
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2011 Markus Kivioja <markus.kivioja@digia.com>
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

#include "box2dropejoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DRopeJoint::Box2DRopeJoint(QObject *parent) :
    Box2DJoint(mRopeJointDef, parent)
{
}

float Box2DRopeJoint::maxLength() const
{
    return world()->toPixels(mRopeJointDef.maxLength);
}

void Box2DRopeJoint::setMaxLength(float maxLength)
{
    const float maxLengthMeters = world()->toMeters(maxLength);
    if (mRopeJointDef.maxLength == maxLengthMeters)
        return;

    mRopeJointDef.maxLength = maxLengthMeters;
    if (ropeJoint())
        ropeJoint()->SetMaxLength(maxLengthMeters);
    emit maxLengthChanged();
}

QPointF Box2DRopeJoint::localAnchorA() const
{
    return world()->toPixels(mRopeJointDef.localAnchorA);
}

void Box2DRopeJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mRopeJointDef.localAnchorA = world()->toMeters(localAnchorA);
    emit localAnchorAChanged();
}

QPointF Box2DRopeJoint::localAnchorB() const
{
    return world()->toPixels(mRopeJointDef.localAnchorB);
}

void Box2DRopeJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mRopeJointDef.localAnchorB = world()->toMeters(localAnchorB);
    emit localAnchorBChanged();
}

b2Joint *Box2DRopeJoint::createJoint()
{
    return world()->world().CreateJoint(&mRopeJointDef);
}

QPointF Box2DRopeJoint::getReactionForce(float32 inv_dt) const
{
    if (ropeJoint())
        return invertY(ropeJoint()->GetReactionForce(inv_dt));
    return QPointF();
}

float Box2DRopeJoint::getReactionTorque(float32 inv_dt) const
{
    if (ropeJoint())
        return ropeJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
