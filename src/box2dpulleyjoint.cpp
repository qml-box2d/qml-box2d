/*
 * box2dpulleyjoint.cpp
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

/*!
   \qmltype PulleyJoint
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
    \brief A PulleyJoint is used to create an idealized pulley.

    The pulley connects two \l {Body} {bodies} to the ground and also to each other. As one
\l {Body}{body} goes up, the other goes down. The total length of the pulley rope is conserved according to the initial
 configuration.

    \code
            localAnchorA: Qt.point(100,0)
            localAnchorB: Qt.point(100,0)
    \endcode

    You can supply a \c ratio that simulates a block and tackle. This causes one side
of the pulley to extend faster than the other. At the same time the constraint force is smaller
on one side than  the other. You can use this to create mechanical leverage.

    \code
            localAnchorA: Qt.point(100,0)
            localAnchorB: Qt.point(100,0)
            ratio: 2
    \endcode

For example, if the \c ratio is 2, then \l{PulleyJoint::lengthA}{length1} will vary at twice the rate of
 \l {PulleyJoint::lengthB}{length2}. Also the force in the rope attached to body1 will have half the constraint force as
the rope attached to body2.

Pulleys can be troublesome when one side is fully extended. The rope on the other side will have zero length. At this point the constraint equations become singular (bad). You should
 configure collision shapes to prevent this.

Here is an example pulley definition:
    \code
        PulleyJoint {
            world: world
            bodyA: bodyA
            bodyB: bodyB
            groundAnchorA: Qt.point(225,100)
            groundAnchorB: Qt.point(575,100)
            localAnchorA: Qt.point(100,0)
            localAnchorB: Qt.point(100,0)
            lengthA: 150
            lengthB: 150
            ratio: 0.2
        }
    \endcode


For more on this see the \l{pulley}{ pulley example}
*/





//////////////////////////////////////////






/*!
  \qmlproperty QPointF PulleyJoint::groundAnchorA

 */
/*!
  \qmlproperty QPointF PulleyJoint::groundAnchorB

 */
/*!
  \qmlproperty QPointF PulleyJoint::localAnchorA

 */
/*!
  \qmlproperty QPointF PulleyJoint::localAnchorB

 */
/*!
  \qmlproperty float PulleyJoint::lengthA
    The total amount of length for the attaches to \c bodyA

 */
/*!
  \qmlproperty float PulleyJoint::lengthB
    The total ammount of length on the rope attached to \c bodyB
 */
/*!
  \qmlproperty float PulleyJoint::ratio
The ammount of gravity that will be used by the PulleyJoint.
to pull it one way or the other. In the first image below we can see that the
left side of the \l {pulley} { example } has been pulled down.  This was acived
by setting the ratio to greater then 1.

\image pullyjoint_ratio1.png

\code
        PulleyJoint {
            ...
            ......
            ratio: 1.5
        }
\endcode

But as you can see in the second image that if we set the the ratio to less then 1 it sets the
gravity to pull the other way on the "string"
\code
        PulleyJoint {
            ...
            ......
            ratio: .5
        }
\endcode

\image pullyjoint_ratio2.png

 */




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

/*!
  \qmlmethod Box2DPulleyJoint::getCurrentLengthA()
 */
float Box2DPulleyJoint::getCurrentLengthA() const
{
    if (pulleyJoint())
        return world()->toPixels(pulleyJoint()->GetCurrentLengthA());
    return lengthA();
}
/*!
 \qmlmethod Box2DPulleyJoint::getCurrentLengthB

 */
float Box2DPulleyJoint::getCurrentLengthB() const
{
    if (pulleyJoint())
        return world()->toPixels(pulleyJoint()->GetCurrentLengthB());
    return lengthB();
}

/*!
 \qmlmethod Box2DPulleyJoint::getReactionForce(float inv_dt)

 */
QPointF Box2DPulleyJoint::getReactionForce(float32 inv_dt) const
{
    if (pulleyJoint())
        return invertY(pulleyJoint()->GetReactionForce(inv_dt));
    return QPointF();
}

/*!
 \qmlmethod Box2DPulleyJoint::getReactionTorque(inv_dt)

 */
float Box2DPulleyJoint::getReactionTorque(float32 inv_dt) const
{
    if (pulleyJoint())
        return pulleyJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
