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

Box2DPulleyJoint::Box2DPulleyJoint(QObject *parent)
    : Box2DJoint(PulleyJoint, parent)
    , m_lengthA(0.0f)
    , m_lengthB(0.0f)
    , m_ratio(1.0f)
    , m_defaultLocalAnchorA(true)
    , m_defaultLocalAnchorB(true)
    , m_defaultLengthA(true)
    , m_defaultLengthB(true)
{
    setCollideConnected(true);
}

void Box2DPulleyJoint::setGroundAnchorA(const QPointF &groundAnchorA)
{
    if (m_groundAnchorA == groundAnchorA)
        return;

    m_groundAnchorA = groundAnchorA;
    emit groundAnchorAChanged();
}

void Box2DPulleyJoint::setGroundAnchorB(const QPointF &groundAnchorB)
{
    if (m_groundAnchorB == groundAnchorB)
        return;

    m_groundAnchorB = groundAnchorB;
    emit groundAnchorBChanged();
}

void Box2DPulleyJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    m_defaultLocalAnchorA = false;

    if (m_localAnchorA == localAnchorA)
        return;

    m_localAnchorA = localAnchorA;
    emit localAnchorAChanged();
}

void Box2DPulleyJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    m_defaultLocalAnchorB = false;

    if (m_localAnchorB == localAnchorB)
        return;

    m_localAnchorB = localAnchorB;
    emit localAnchorBChanged();
}

void Box2DPulleyJoint::setLengthA(float lengthA)
{
    m_defaultLengthA = false;

    if (m_lengthA == lengthA)
        return;

    m_lengthA = lengthA;
    emit lengthAChanged();
}

void Box2DPulleyJoint::setLengthB(float lengthB)
{
    m_defaultLengthB = false;

    if (m_lengthB == lengthB)
        return;

    m_lengthB = lengthB;
    emit lengthBChanged();
}

void Box2DPulleyJoint::setRatio(float ratio)
{
    if (m_ratio == ratio)
        return;

    m_ratio = ratio;
    emit ratioChanged();
}

b2Joint *Box2DPulleyJoint::createJoint()
{
    b2PulleyJointDef jointDef;
    initializeJointDef(jointDef);

    jointDef.groundAnchorA = world()->toMeters(m_groundAnchorA);
    jointDef.groundAnchorB = world()->toMeters(m_groundAnchorB);

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

    if (m_defaultLengthA) {
        b2Vec2 anchorA = jointDef.bodyA->GetWorldPoint(jointDef.localAnchorA);
        jointDef.lengthA = (anchorA - jointDef.groundAnchorA).Length();
    } else {
        jointDef.lengthA = world()->toMeters(m_lengthA);
    }

    if (m_defaultLengthB) {
        b2Vec2 anchorB = jointDef.bodyB->GetWorldPoint(jointDef.localAnchorB);
        jointDef.lengthB = (anchorB - jointDef.groundAnchorB).Length();
    } else {
        jointDef.lengthB = world()->toMeters(m_lengthB);
    }

    if (qFuzzyIsNull(jointDef.lengthA) || qFuzzyIsNull(jointDef.lengthB)) {
        qWarning() << "PulleyJoint: the joint length cannot be zero";
        return 0;
    }

    jointDef.ratio = m_ratio;

    return world()->world().CreateJoint(&jointDef);
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
