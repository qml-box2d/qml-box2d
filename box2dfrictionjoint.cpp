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

Box2DFrictionJoint::Box2DFrictionJoint(QObject *parent) :
    Box2DJoint(mFrictionJointDef, parent),
    mAnchorsAuto(true)
{
}

void Box2DFrictionJoint::setMaxForce(float maxForce)
{
    if (!(b2IsValid(maxForce) && maxForce >= 0.0f)) {
        qWarning() << "FrictionJoint: Invalid maxForce:" << maxForce;
        return;
    }
    if (mFrictionJointDef.maxForce == maxForce)
        return;

    mFrictionJointDef.maxForce = maxForce;
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
    if (mFrictionJointDef.maxTorque == maxTorque)
        return;

    mFrictionJointDef.maxTorque = maxTorque;
    if (frictionJoint())
        frictionJoint()->SetMaxTorque(maxTorque);
    emit maxTorqueChanged();
}

QPointF Box2DFrictionJoint::localAnchorA() const
{
    if (frictionJoint())
        return QPointF(frictionJoint()->GetAnchorA().x * scaleRatio,
                       -frictionJoint()->GetAnchorA().y * scaleRatio);
    return QPointF(mFrictionJointDef.localAnchorA.x * scaleRatio,
                   -mFrictionJointDef.localAnchorA.y * scaleRatio);
}

void Box2DFrictionJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    mFrictionJointDef.localAnchorA = b2Vec2(localAnchorA.x() / scaleRatio,
                                            -localAnchorA.y() / scaleRatio);
    mAnchorsAuto = false;
    emit localAnchorAChanged();
}

QPointF Box2DFrictionJoint::localAnchorB() const
{
    if (frictionJoint())
        return QPointF(frictionJoint()->GetAnchorB().x * scaleRatio,
                       -frictionJoint()->GetAnchorB().y * scaleRatio);
    return QPointF(mFrictionJointDef.localAnchorB.x * scaleRatio,
                   -mFrictionJointDef.localAnchorB.y * scaleRatio);
}

void Box2DFrictionJoint::setLocalAnchorB(const QPointF &localAnchorB)
{
    mFrictionJointDef.localAnchorB = b2Vec2(localAnchorB.x() / scaleRatio,
                                            -localAnchorB.y() / scaleRatio);
    mAnchorsAuto = false;
    emit localAnchorBChanged();
}

b2Joint *Box2DFrictionJoint::createJoint()
{
    if (mAnchorsAuto) {
        mFrictionJointDef.Initialize(bodyA()->body(),
                                     bodyB()->body(),
                                     bodyA()->body()->GetWorldCenter());
    } else {
        mFrictionJointDef.bodyA = bodyA()->body();
        mFrictionJointDef.bodyB = bodyB()->body();
    }

    return world()->CreateJoint(&mFrictionJointDef);
}

QPointF Box2DFrictionJoint::getReactionForce(float32 inv_dt) const
{
    if (frictionJoint()) {
        b2Vec2 point = frictionJoint()->GetReactionForce(inv_dt);
        return QPointF(point.x * scaleRatio, point.y * scaleRatio);
    }
    return QPointF();
}

float Box2DFrictionJoint::getReactionTorque(float32 inv_dt) const
{
    if (frictionJoint())
        return frictionJoint()->GetReactionTorque(inv_dt);
    return 0.0f;
}
