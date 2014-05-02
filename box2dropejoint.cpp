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

Box2DRopeJoint::Box2DRopeJoint(QObject *parent)
    : Box2DJoint(RopeJoint, parent)
    , m_maxLength(0.0f)
    , m_defaultLocalAnchorA(true)
    , m_defaultLocalAnchorB(true)
{
}

void Box2DRopeJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    m_defaultLocalAnchorA = false;

    if (m_localAnchorA == localAnchorA)
        return;

    m_localAnchorA = localAnchorA;
    emit localAnchorAChanged();
}

void Box2DRopeJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    m_defaultLocalAnchorB = false;

    if (m_localAnchorB == localAnchorB)
        return;

    m_localAnchorB = localAnchorB;
    emit localAnchorBChanged();
}

void Box2DRopeJoint::setMaxLength(float maxLength)
{
    if (m_maxLength == maxLength)
        return;

    m_maxLength = maxLength;
    if (ropeJoint()) {
        const float maxLengthMeters = world()->toMeters(maxLength);
        if (maxLengthMeters < b2_linearSlop)
            qWarning() << "RopeJoint: maxLength too small";

        ropeJoint()->SetMaxLength(maxLengthMeters);
    }
    emit maxLengthChanged();
}

b2Joint *Box2DRopeJoint::createJoint()
{
    b2RopeJointDef jointDef;
    initializeJointDef(jointDef);

    // Default localAnchorA to bodyA center
    if (m_defaultLocalAnchorA)
        jointDef.localAnchorA = jointDef.bodyA->GetLocalCenter();
    else
        jointDef.localAnchorA = world()->toMeters(m_localAnchorA);

    // Default localAnchorB to bodyB center
    if (m_defaultLocalAnchorB)
        jointDef.localAnchorB = jointDef.bodyB->GetLocalCenter();
    else
        jointDef.localAnchorB = world()->toMeters(m_localAnchorB);

    jointDef.maxLength = world()->toMeters(m_maxLength);

    if (jointDef.maxLength < b2_linearSlop)
        qWarning() << "RopeJoint: maxLength too small";

    return world()->world().CreateJoint(&jointDef);
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
