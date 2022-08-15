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

Box2DDistanceJoint::Box2DDistanceJoint(QObject *parent)
    : Box2DJoint(DistanceJoint, parent)
    , m_length(1.0f)
    , m_stiffness(0.0f)
    , m_damping(0.0f)
    , m_defaultLocalAnchorA(true)
    , m_defaultLocalAnchorB(true)
    , m_defaultLength(true)
{
}

void Box2DDistanceJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    m_defaultLocalAnchorA = false;

    if (m_localAnchorA == localAnchorA)
        return;

    m_localAnchorA = localAnchorA;
    emit localAnchorAChanged();
}

void Box2DDistanceJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    m_defaultLocalAnchorB = false;

    if (m_localAnchorB == localAnchorB)
        return;

    m_localAnchorB = localAnchorB;
    emit localAnchorBChanged();
}

void Box2DDistanceJoint::setLength(float length)
{
    if (m_length == length)
        return;

    m_length = length;
    m_defaultLength = false;
    if (distanceJoint())
        distanceJoint()->SetLength(world()->toMeters(length));
    emit lengthChanged();
}

void Box2DDistanceJoint::setStiffness(float stiffness)
{
    if (m_stiffness == stiffness)
        return;

    m_stiffness = stiffness;
    if (distanceJoint())
        distanceJoint()->SetStiffness(stiffness);
    emit stiffnessChanged();
}

void Box2DDistanceJoint::setDamping(float damping)
{
    if (m_damping == damping)
        return;

    m_damping = damping;
    if (distanceJoint())
        distanceJoint()->SetDamping(damping);
    emit dampingChanged();
}

b2Joint *Box2DDistanceJoint::createJoint()
{
    b2DistanceJointDef jointDef;
    initializeJointDef(jointDef);

    // Default to bodyA center
    if (m_defaultLocalAnchorA)
        jointDef.localAnchorA = jointDef.bodyA->GetLocalCenter();
    else
        jointDef.localAnchorA = world()->toMeters(m_localAnchorA);

    // Default to bodyB center
    if (m_defaultLocalAnchorB)
        jointDef.localAnchorB = jointDef.bodyB->GetLocalCenter();
    else
        jointDef.localAnchorB = world()->toMeters(m_localAnchorB);

    // Default to length between anchors
    if (m_defaultLength) {
        b2Vec2 a = jointDef.bodyA->GetWorldPoint(jointDef.localAnchorA);
        b2Vec2 b = jointDef.bodyB->GetWorldPoint(jointDef.localAnchorB);
        jointDef.length = (b - a).Length();
    } else {
        jointDef.length = world()->toMeters(m_length);
    }

    jointDef.stiffness = m_stiffness;
    jointDef.damping = m_damping;

    return world()->world().CreateJoint(&jointDef);
}

QPointF Box2DDistanceJoint::getReactionForce(float inv_dt) const
{
    if (distanceJoint())
        return invertY(distanceJoint()->GetReactionForce(inv_dt));
    return QPointF();
}

float Box2DDistanceJoint::getReactionTorque(float inv_dt) const
{
    if (distanceJoint())
        return distanceJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
