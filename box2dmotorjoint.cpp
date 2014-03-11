/*
 * box2dmotorjoint.cpp
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2011 Markus Kivioja <markus.kivioja@digia.com>
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

#include "box2dmotorjoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DMotorJoint::Box2DMotorJoint(QObject *parent) :
    Box2DJoint(parent),
    mMotorJointDef(),
    mMotorJoint(0)
{
}

Box2DMotorJoint::~Box2DMotorJoint()
{
    cleanup(world());
}

QPointF Box2DMotorJoint::linearOffset() const
{
    return QPointF(mMotorJointDef.linearOffset.x * scaleRatio,mMotorJointDef.linearOffset.y * scaleRatio);
}

void Box2DMotorJoint::setLinearOffset(const QPointF &linearOffset)
{
    if(this->linearOffset() == linearOffset)
        return;
    mMotorJointDef.linearOffset = b2Vec2(linearOffset.x() / scaleRatio,-linearOffset.y() / scaleRatio);
    if(mMotorJoint)
        mMotorJoint->SetLinearOffset(mMotorJointDef.linearOffset);
    emit linearOffsetChanged();
}

float Box2DMotorJoint::angularOffset() const
{
    return mMotorJointDef.angularOffset * 180 / b2_pi;
}

void Box2DMotorJoint::setAngularOffset(const float angularOffset)
{
    float angularOffsetRad = angularOffset * ( b2_pi / 180);
    if(mMotorJointDef.angularOffset == angularOffsetRad)
        return;
    mMotorJointDef.angularOffset = angularOffsetRad;
    if(mMotorJoint)
        mMotorJoint->SetAngularOffset(angularOffsetRad);
    emit angularOffsetChanged();
}

float Box2DMotorJoint::maxForce() const
{
    return mMotorJointDef.maxForce;
}

void Box2DMotorJoint::setMaxForce(const float maxForce)
{
    if(mMotorJointDef.maxForce == maxForce)
        return;
    mMotorJointDef.maxForce = maxForce;
    if(mMotorJoint)
        mMotorJoint->SetMaxForce(maxForce);
    emit maxForceChanged();
}

float Box2DMotorJoint::maxTorque() const
{
    return mMotorJointDef.maxTorque;
}

void Box2DMotorJoint::setMaxTorque(const float maxTorque)
{
    if(mMotorJointDef.maxTorque == maxTorque)
        return;
    mMotorJointDef.maxTorque = maxTorque;
    if(mMotorJoint)
        mMotorJoint->SetMaxTorque(maxTorque);
    emit maxTorqueChanged();
}

float Box2DMotorJoint::correctionFactor() const
{
    return mMotorJointDef.correctionFactor;
}

void Box2DMotorJoint::setCorrectionFactor(const float correctionFactor)
{
    if(mMotorJointDef.correctionFactor == correctionFactor)
        return;
    mMotorJointDef.correctionFactor = correctionFactor;
    if(mMotorJoint)
        mMotorJoint->SetCorrectionFactor(correctionFactor);
    emit correctionFactorChanged();
}

void Box2DMotorJoint::nullifyJoint()
{
    mMotorJoint = 0;
}

void Box2DMotorJoint::createJoint()
{

    mMotorJointDef.Initialize(bodyA()->body(),bodyB()->body());
    mMotorJointDef.collideConnected = collideConnected();
    mMotorJoint = static_cast<b2MotorJoint*>(
                world()->CreateJoint(&mMotorJointDef));
    mMotorJoint->SetUserData(this);
    mInitializePending = false;
    emit created();
}

void Box2DMotorJoint::cleanup(b2World *world)
{
    if(!world) {
        qWarning() << "MotorJoint: There is no world connected";
        return;
    }
    if (mMotorJoint && bodyA() && bodyB()) {
        mMotorJoint->SetUserData(0);
        world->DestroyJoint(mMotorJoint);
        mMotorJoint = 0;
    }
}

b2Joint *Box2DMotorJoint::GetJoint()
{
    return mMotorJoint;
}
