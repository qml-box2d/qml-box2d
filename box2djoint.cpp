/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the Box2D QML plugin.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library;  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2djoint.h"
#include "box2dbody.h"
#include "box2dworld.h"

Box2DJoint::Box2DJoint(QObject *parent) :
    QObject(parent),
    mInitializePending(false),
    mWorld(0),
    mCollideConnected(false),
    mBodyA(0),
    mBodyB(0)
{
}

bool Box2DJoint::collideConnected() const
{
    return mCollideConnected;
}

void Box2DJoint::setCollideConnected(bool collideConnected)
{
    if (mCollideConnected == collideConnected)
        return;

    mCollideConnected = collideConnected;

    emit collideConnectedChanged();
}

Box2DWorld *Box2DJoint::box2DWorld() const
{
    return mWorld;
}

void Box2DJoint::setWorld(Box2DWorld *world)
{
    if (mWorld == world)
        return;

    mWorld = world;
    emit worldChanged();
    initialize();
}

Box2DBody *Box2DJoint::bodyA() const
{
    return mBodyA;
}

void Box2DJoint::setBodyA(Box2DBody *bodyA)
{
    if (mBodyA)
        return;

    if (bodyA->body() != NULL) {
        mBodyA = bodyA;
        emit bodyAChanged();
        initialize();
    }
    else
        connect(bodyA, SIGNAL(bodyCreated()), this, SLOT(bodyACreated()));
}

Box2DBody *Box2DJoint::bodyB() const
{
    return mBodyB;
}

void Box2DJoint::setBodyB(Box2DBody *bodyB)
{
    if (mBodyB)
        return;

    if (bodyB->body() != NULL) {
        mBodyB = bodyB;
        emit bodyBChanged();
        initialize();
    }
    else
        connect(bodyB, SIGNAL(bodyCreated()), this, SLOT(bodyBCreated()));
}

void Box2DJoint::initialize()
{
    if (!mBodyA || !mBodyB || !mWorld) {
        // When components are created dynamically, they get their parent
        // assigned before they have been completely initialized. In that case
        // we need to delay initialization.
        mInitializePending = true;
        return;
    }

    createJoint();
}

b2World *Box2DJoint::world() const
{
    return mWorld->world();
}

void Box2DJoint::bodyACreated()
{
    mBodyA = static_cast<Box2DBody*>(sender());
    emit bodyAChanged();
    initialize();
}

void Box2DJoint::bodyBCreated()
{
    mBodyB = static_cast<Box2DBody*>(sender());
    emit bodyBChanged();
    initialize();
}
