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
    Box2DJoint(parent),
    mGearJointDef(),
    mGearJoint(0)
{
}

Box2DGearJoint::~Box2DGearJoint()
{
    cleanup(world());
}

float Box2DGearJoint::ratio() const
{
    if(mGearJoint) mGearJoint->GetRatio();
    return mGearJointDef.ratio;
}

void Box2DGearJoint::setRatio(float _ratio)
{
    if(qFuzzyCompare(_ratio,ratio())) return;
    mGearJointDef.ratio = _ratio;
    if(mGearJoint) mGearJoint->SetRatio(_ratio);
    emit ratioChanged();
}

Box2DJoint *Box2DGearJoint::joint1() const
{
    if(mGearJoint) return toBox2DJoint(mGearJoint->GetJoint1());
    return toBox2DJoint(mGearJointDef.joint1);
}

void Box2DGearJoint::setJoint1(Box2DJoint *_joint1)
{
    if(_joint1 == joint1()) return;
    mGearJointDef.joint1 = _joint1->GetJoint();
    if(mGearJointDef.joint1)
    {
        initialize();
        emit joint1Changed();
    }
    else connect(_joint1,SIGNAL(created()),this,SLOT(joint1Created()));
}

Box2DJoint *Box2DGearJoint::joint2() const
{
    if(mGearJoint) return toBox2DJoint(mGearJoint->GetJoint2());
    return toBox2DJoint(mGearJointDef.joint2);
}

void Box2DGearJoint::setJoint2(Box2DJoint *_joint2)
{
    if(_joint2 == joint2()) return;
    mGearJointDef.joint2 = _joint2->GetJoint();
    if(mGearJointDef.joint2)
    {
        initialize();
        emit joint2Changed();
    }
    else connect(_joint2,SIGNAL(created()),this,SLOT(joint2Created()));
}

void Box2DGearJoint::nullifyJoint()
{
    mGearJoint = 0;
}

void Box2DGearJoint::createJoint()
{    
    if(!mGearJointDef.joint1 || !mGearJointDef.joint2) return;
    mGearJointDef.bodyA = bodyA()->body();
    mGearJointDef.bodyB = bodyB()->body();

    mGearJoint = static_cast<b2GearJoint*>
            (world()->CreateJoint(&mGearJointDef));
    mGearJoint->SetUserData(this);
    mInitializePending = false;
    emit created();
}

void Box2DGearJoint::cleanup(b2World *world)
{
    if(!world) {
        qWarning() << "GearJoint: There is no world connected";
        return;
    }
    if (mGearJoint) {
        mGearJoint->SetUserData(0);
        world->DestroyJoint(mGearJoint);
        mGearJoint = 0;
    }
}

b2Joint *Box2DGearJoint::GetJoint()
{
    return mGearJoint;
}

void Box2DGearJoint::joint1Created()
{
    Box2DJoint * joint1 = static_cast<Box2DJoint *>(sender());
    mGearJointDef.joint1 = joint1->GetJoint();
    initialize();
}

void Box2DGearJoint::joint2Created()
{
    Box2DJoint * joint2 = static_cast<Box2DJoint *>(sender());
    mGearJointDef.joint2 = joint2->GetJoint();
    initialize();
}


