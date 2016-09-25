/*
 * box2dmousejoint.cpp
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

#include "box2dmousejoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

/*!
   \qmltype MouseJoint
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
    \brief The MouseJoint is used to manipulate bodies with the mouse.

It attempts to drive a point on a Body towards the current position of the cursor. There is no
restriction on rotation. The MouseJoint definition has a \c target point, \c maxForce, \c frequencyHz,
and \c dampingRatio. The target point initially coincides with the Body ’s anchor point.
The \c maxForce is used to prevent violent outcomes
*/

/////////////////////////////////


/*!
 \qmlproperty float MouseJoint::dampingRatio
    The damping ratio that is allowed to the element.
 */

/*!
 \qmlproperty float MouseJoint::frequencyHz
    The frequency that one would like to use on the MouseJoint
 */

/*!
 \qmlproperty float MouseJoint::maxForce
    The maxium ammount of force that is allowed to the MouseJoint
 */

/*!
 \qmlproperty Qt.point MouseJoint::target
    The item in which you want to target, for the MouseJoint
 */

Box2DMouseJoint::Box2DMouseJoint(QObject *parent)
    : Box2DJoint(MouseJoint, parent)
    , m_maxForce(0.0f)
    , m_frequencyHz(5.0f)
    , m_dampingRatio(0.7f)
{
}

void Box2DMouseJoint::setDampingRatio(float dampingRatio)
{
    if (m_dampingRatio == dampingRatio)
        return;

    m_dampingRatio = dampingRatio;
    if (mouseJoint())
        mouseJoint()->SetDampingRatio(dampingRatio);
    emit dampingRatioChanged();
}

void Box2DMouseJoint::setFrequencyHz(float frequencyHz)
{
    if (m_frequencyHz == frequencyHz)
        return;

    m_frequencyHz = frequencyHz;
    if (mouseJoint())
        mouseJoint()->SetFrequency(frequencyHz);
    emit frequencyHzChanged();
}

void Box2DMouseJoint::setMaxForce(float maxForce)
{
    if (m_maxForce == maxForce)
        return;

    m_maxForce = maxForce;
    if (mouseJoint())
        mouseJoint()->SetMaxForce(maxForce);
    emit maxForceChanged();
}

void Box2DMouseJoint::setTarget(const QPointF &target)
{
    if (m_target == target)
        return;

    m_target = target;
    if (mouseJoint())
        mouseJoint()->SetTarget(world()->toMeters(target));
    emit targetChanged();
}

b2Joint *Box2DMouseJoint::createJoint()
{
    b2MouseJointDef jointDef;
    initializeJointDef(jointDef);

    jointDef.target = world()->toMeters(m_target);
    jointDef.maxForce = m_maxForce;
    jointDef.frequencyHz = m_frequencyHz;
    jointDef.dampingRatio = m_dampingRatio;

    return world()->world().CreateJoint(&jointDef);
}
/*!
\qmlmethod MouseJoint::getReactionForce(inv_dt)
    Returns the current force.
*/
QPointF Box2DMouseJoint::getReactionForce(float32 inv_dt) const
{
    if (mouseJoint())
        return invertY(mouseJoint()->GetReactionForce(inv_dt));
    return QPointF();
}
/*!
 \qmlmethod MouseJoint::getReactionTorque(inv_dt)
    Returns the current torque
*/
float Box2DMouseJoint::getReactionTorque(float32 inv_dt) const
{
    if (mouseJoint())
        return mouseJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
