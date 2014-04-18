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

#include "box2dgearjoint.h"
#include "box2dworld.h"
#include "box2dbody.h"

Box2DGearJoint::Box2DGearJoint(QObject *parent) :
    Box2DJoint(mGearJointDef, parent),
    mJoint1(0),
    mJoint2(0)
{
}

void Box2DGearJoint::setRatio(float ratio)
{
    if (!b2IsValid(ratio)) {
        qWarning() << "GearJoint: Invalid ratio:" << ratio;
        return;
    }
    if (mGearJointDef.ratio == ratio)
        return;

    mGearJointDef.ratio = ratio;
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
    if (mJoint1 == joint1)
        return;

    if (!validJoint(joint1)) {
        qWarning() << "GearJoint.joint1: Invalid joint type";
        joint1 = 0;
    }

    mJoint1 = joint1;

    if (!joint1 || joint1->joint())
        initialize();
    else
        connect(joint1, SIGNAL(created()), this, SLOT(joint1Created()));

    emit joint1Changed();
}

void Box2DGearJoint::setJoint2(Box2DJoint *joint2)
{
    if (mJoint2 == joint2)
        return;

    if (!validJoint(joint2)) {
        qWarning() << "GearJoint.joint2: Invalid joint type";
        joint2 = 0;
    }

    mJoint2 = joint2;

    if (!joint2 || joint2->joint())
        initialize();
    else
        connect(joint2, SIGNAL(created()), this, SLOT(joint2Created()));

    emit joint2Changed();
}

b2Joint *Box2DGearJoint::createJoint()
{
    if (!mJoint1 || !mJoint2)
        return 0;
    if (!mJoint1->joint() || !mJoint2->joint())
        return 0;

    mGearJointDef.joint1 = mJoint1->joint();
    mGearJointDef.joint2 = mJoint2->joint();

    return world()->world().CreateJoint(&mGearJointDef);
}

void Box2DGearJoint::joint1Created()
{
    disconnect(mJoint1, SIGNAL(created()), this, SLOT(joint1Created()));
    initialize();
}

void Box2DGearJoint::joint2Created()
{
    disconnect(mJoint2, SIGNAL(created()), this, SLOT(joint2Created()));
    initialize();
}
