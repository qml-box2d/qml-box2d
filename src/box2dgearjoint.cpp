/*
 * box2dgearjoint.cpp
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

#include "box2dgearjoint.h"
#include "box2dworld.h"
#include "box2dbody.h"

/*!
   \qmltype GearJoint
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
   \brief If you want to create a sophisticated mechanical contraption you might want to use
 gears.

In principle you can create gears in Box2D by using compound \l{Body}{bodies} to model gear
teeth. This is not very efficient and might be tedious to author. You also have to be careful to
line up the gears so the teeth mesh smoothly. Box2D has a simpler method of creating gears:
the GearJoint.

The gear joint can only connect RevoluteJoint and/or PrismaticJoint.
Like the PulleyJoints property \c PulleyJoints::ratio ,you can specify a gear ratio.

Also keep in mind that when one Joint is a RevoluteJoint (angular) and the other Joint is
PrismaticJoint (translation), And then the gear ratio will have units of length or one over length.
Here is an example gear joint. The bodies bodyA and bodyB are any bodies from
the two joints, As long as they are not the same bodies.

    \code
        GearJoint {
            id: gearJoint
            world: world
            bodyA: lever
            bodyB: damper
            joint1: revoluteJoint
            joint2: prismaticJoint
            ratio: 0.05
        }
    \endcode

\b{Example}

\l{gear}{GearJoint Example}

*/




/*!
\qmlproperty float GearJoint::ratio
See \{PulleyJoint::ratio}{pulley ratio}
*/

/*!
\qmlproperty string GearJoint::joint1
    DOCME
*/

/*!
\qmlproperty string GearJoint::joint2
    DOCME
*/

Box2DGearJoint::Box2DGearJoint(QObject *parent)
    : Box2DJoint(GearJoint, parent)
    , m_joint1(0)
    , m_joint2(0)
    , m_ratio(1.0f)
{
}

void Box2DGearJoint::setRatio(float ratio)
{
    if (!b2IsValid(ratio)) {
        qWarning() << "GearJoint: Invalid ratio:" << ratio;
        return;
    }
    if (m_ratio == ratio)
        return;

    m_ratio = ratio;
    if (gearJoint())
        gearJoint()->SetRatio(ratio);
    emit ratioChanged();
}

static bool validJoint(Box2DJoint *joint)
{
    if (!joint)
        return true;

    const Box2DJoint::JointType type = joint->jointType();
    return type == Box2DJoint::RevoluteJoint ||
            type == Box2DJoint::PrismaticJoint;
}

void Box2DGearJoint::setJoint1(Box2DJoint *joint1)
{
    if (m_joint1 == joint1)
        return;

    if (!validJoint(joint1)) {
        qWarning() << "GearJoint.joint1: Invalid joint type";
        joint1 = 0;
    }

    m_joint1 = joint1;

    if (!joint1 || joint1->joint())
        initialize();
    else
        connect(joint1, SIGNAL(created()), this, SLOT(joint1Created()));

    emit joint1Changed();
}

void Box2DGearJoint::setJoint2(Box2DJoint *joint2)
{
    if (m_joint2 == joint2)
        return;

    if (!validJoint(joint2)) {
        qWarning() << "GearJoint.joint2: Invalid joint type";
        joint2 = 0;
    }

    m_joint2 = joint2;

    if (!joint2 || joint2->joint())
        initialize();
    else
        connect(joint2, SIGNAL(created()), this, SLOT(joint2Created()));

    emit joint2Changed();
}

b2Joint *Box2DGearJoint::createJoint()
{
    if (!m_joint1 || !m_joint2)
        return 0;
    if (!m_joint1->joint() || !m_joint2->joint())
        return 0;

    b2GearJointDef jointDef;
    initializeJointDef(jointDef);

    jointDef.joint1 = m_joint1->joint();
    jointDef.joint2 = m_joint2->joint();
    jointDef.ratio = m_ratio;

    return world()->world().CreateJoint(&jointDef);
}

void Box2DGearJoint::joint1Created()
{
    disconnect(m_joint1, SIGNAL(created()), this, SLOT(joint1Created()));
    initialize();
}

void Box2DGearJoint::joint2Created()
{
    disconnect(m_joint2, SIGNAL(created()), this, SLOT(joint2Created()));
    initialize();
}
