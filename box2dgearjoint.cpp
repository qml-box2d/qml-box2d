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
    Box2DJoint(parent)
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

Box2DJoint *Box2DGearJoint::joint1() const
{
    return mGearJointDef.joint1 ? toBox2DJoint(mGearJointDef.joint1) : 0;
}

void Box2DGearJoint::setJoint1(Box2DJoint *_joint1)
{
    if (_joint1 == joint1())
        return;
    mGearJointDef.joint1 = _joint1->joint();
    if (mGearJointDef.joint1) {
        initialize();
        emit joint1Changed();
    }
    else connect(_joint1, SIGNAL(created()), this, SLOT(joint1Created()));
}

Box2DJoint *Box2DGearJoint::joint2() const
{
    return mGearJointDef.joint2 ? toBox2DJoint(mGearJointDef.joint2) : 0;
}

void Box2DGearJoint::setJoint2(Box2DJoint *_joint2)
{
    if (_joint2 == joint2())
        return;
    mGearJointDef.joint2 = _joint2->joint();
    if (mGearJointDef.joint2) {
        initialize();
        emit joint2Changed();
    }
    else connect(_joint2, SIGNAL(created()), this, SLOT(joint2Created()));
}

b2Joint *Box2DGearJoint::createJoint()
{    
    if (!mGearJointDef.joint1 || !mGearJointDef.joint2)
        return 0;
    mGearJointDef.bodyA = bodyA()->body();
    mGearJointDef.bodyB = bodyB()->body();

    return world()->CreateJoint(&mGearJointDef);
}

void Box2DGearJoint::joint1Created()
{
    Box2DJoint * joint1 = static_cast<Box2DJoint *>(sender());
    mGearJointDef.joint1 = joint1->joint();
    initialize();
}

void Box2DGearJoint::joint2Created()
{
    Box2DJoint * joint2 = static_cast<Box2DJoint *>(sender());
    mGearJointDef.joint2 = joint2->joint();
    initialize();
}
