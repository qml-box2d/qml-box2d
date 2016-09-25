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

/*!
   \qmltype WeldJoint
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
\brief The WeldJoint attempts to constrain all relative motion between two bodies.
It is tempting to use the WeldJoint to define breakable structures. However, the Box2D
 solver is iterative so the joints are a bit soft. So chains of bodies connected by WeldJoints
will flex. Instead it is better to create breakable bodies starting with a single body with
multiple fixtures. When the Body breaks, you can destroy a fixture and recreate it on a
new body.

\l { weld} { Example of using a weld joint in QML}.

*/



/*!
 \qmlproperty QPointF WeldJoint::localAnchorA
 The local anchor point associated with bodyA
 */

/*!
   \qmlproperty QPointF WeldJoint::localAnchorB
    The local anchor point associated with bodyB
 */

/*!
   \qmlproperty float WeldJoint::referenceAngle
    The angle in which the WeldJoint is held together
 */

/*!
   \qmlproperty float WeldJoint::frequencyHz
    Allows one to set the frequency of the WeldJoint.
 */

/*!
   \qmlproperty float WeldJoint::dampingRatio
    Allows one to set the dampingRatio of the WeldJoint.
 */

Box2DWeldJoint::Box2DWeldJoint(QObject *parent)
    : Box2DJoint(WeldJoint, parent)
    , m_referenceAngle(0.0f)
    , m_frequencyHz(0.0f)
    , m_dampingRatio(0.0f)
    , m_defaultLocalAnchorA(true)
    , m_defaultLocalAnchorB(true)
    , m_defaultReferenceAngle(true)
{
}

void Box2DWeldJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    m_defaultLocalAnchorA = false;

    if (m_localAnchorA == localAnchorA)
        return;

    m_localAnchorA = localAnchorA;
    emit localAnchorAChanged();
}

void Box2DWeldJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    m_defaultLocalAnchorB = false;

    if (m_localAnchorB == localAnchorB)
        return;

    m_localAnchorB = localAnchorB;
    emit localAnchorBChanged();
}

void Box2DWeldJoint::setReferenceAngle(float referenceAngle)
{
    m_defaultReferenceAngle = false;

    if (m_referenceAngle == referenceAngle)
        return;

    m_referenceAngle = referenceAngle;
    emit referenceAngleChanged();
}

void Box2DWeldJoint::setFrequencyHz(float frequencyHz)
{
    if (m_frequencyHz == frequencyHz)
        return;

    m_frequencyHz = frequencyHz;
    if (weldJoint())
        weldJoint()->SetFrequency(frequencyHz);
    emit frequencyHzChanged();
}

void Box2DWeldJoint::setDampingRatio(float dampingRatio)
{
    if (m_dampingRatio == dampingRatio)
        return;

    m_dampingRatio = dampingRatio;
    if (weldJoint())
        weldJoint()->SetDampingRatio(dampingRatio);
    emit dampingRatioChanged();
}

b2Joint *Box2DWeldJoint::createJoint()
{
    b2WeldJointDef jointDef;
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

    if (m_defaultReferenceAngle) {
        float32 angleA = jointDef.bodyA->GetAngle();
        float32 angleB = jointDef.bodyB->GetAngle();
        jointDef.referenceAngle = angleB - angleA;
    } else {
        jointDef.referenceAngle = toRadians(m_referenceAngle);
    }

    jointDef.frequencyHz = m_frequencyHz;
    jointDef.dampingRatio = m_dampingRatio;

    return world()->world().CreateJoint(&jointDef);
}

QPointF Box2DWeldJoint::localAnchorA() const
{
    return m_localAnchorA;
}

QPointF Box2DWeldJoint::localAnchorB() const
{
    return m_localAnchorB;
}

float Box2DWeldJoint::referenceAngle() const
{
    return m_referenceAngle;
}
