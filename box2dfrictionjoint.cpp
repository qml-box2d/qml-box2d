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

#include "box2dfrictionjoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DFrictionJoint::Box2DFrictionJoint(QObject *parent)
    : Box2DJoint(FrictionJoint, parent)
    , m_maxForce(0.0f)
    , m_maxTorque(0.0f)
    , m_defaultLocalAnchorA(true)
    , m_defaultLocalAnchorB(true)
{
}

void Box2DFrictionJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    m_defaultLocalAnchorA = false;

    if (m_localAnchorA == localAnchorA)
        return;

    m_localAnchorA = localAnchorA;
    emit localAnchorAChanged();
}

void Box2DFrictionJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    m_defaultLocalAnchorB = false;

    if (m_localAnchorB == localAnchorB)
        return;

    m_localAnchorB = localAnchorB;
    emit localAnchorBChanged();
}

void Box2DFrictionJoint::setMaxForce(float maxForce)
{
    if (!(b2IsValid(maxForce) && maxForce >= 0.0f)) {
        qWarning() << "FrictionJoint: Invalid maxForce:" << maxForce;
        return;
    }
    if (m_maxForce == maxForce)
        return;

    m_maxForce = maxForce;
    if (frictionJoint())
        frictionJoint()->SetMaxForce(maxForce);
    emit maxForceChanged();
}

void Box2DFrictionJoint::setMaxTorque(float maxTorque)
{
    if (!(b2IsValid(maxTorque) && maxTorque >= 0.0f)) {
        qWarning() << "FrictionJoint: Invalid maxTorque:" << maxTorque;
        return;
    }
    if (m_maxTorque == maxTorque)
        return;

    m_maxTorque = maxTorque;
    if (frictionJoint())
        frictionJoint()->SetMaxTorque(maxTorque);
    emit maxTorqueChanged();
}

b2Joint *Box2DFrictionJoint::createJoint()
{
    b2FrictionJointDef jointDef;
    initializeJointDef(jointDef);

    // Default localAnchorA to bodyA center
    if (m_defaultLocalAnchorA)
        jointDef.localAnchorA = jointDef.bodyA->GetLocalCenter();
    else
        jointDef.localAnchorA = world()->toMeters(m_localAnchorA);

    // Default localAnchorB to the same world position as localAnchorA
    if (m_defaultLocalAnchorB) {
        b2Vec2 anchorA = jointDef.bodyA->GetWorldPoint(jointDef.localAnchorA);
        jointDef.localAnchorB = jointDef.bodyB->GetLocalPoint(anchorA);
    } else {
        jointDef.localAnchorB = world()->toMeters(m_localAnchorB);
    }

    jointDef.maxForce = m_maxForce;
    jointDef.maxTorque = m_maxTorque;

    return world()->world().CreateJoint(&jointDef);
}

QPointF Box2DFrictionJoint::getReactionForce(float32 inv_dt) const
{
    if (frictionJoint())
        return invertY(frictionJoint()->GetReactionForce(inv_dt));
    return QPointF();
}

float Box2DFrictionJoint::getReactionTorque(float32 inv_dt) const
{
    if (frictionJoint())
        return frictionJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
