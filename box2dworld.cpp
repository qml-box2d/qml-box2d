/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the QmlArcade.
 *
 * QmlArcade is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * QmlArcade is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QmlArcade.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2dworld.h"

#include "box2dbody.h"

#include <QTimerEvent>

#include <Box2D.h>

Box2DWorld::Box2DWorld(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    mWorld(0),
    mTimeStep(1.0f / 60.0f),
    mVelocityIterations(10),
    mPositionIterations(10),
    mFrameTime(1000 / 60),
    mTimerId(0)
{
}

Box2DWorld::~Box2DWorld()
{
    delete mWorld;
}

void Box2DWorld::componentComplete()
{
    b2Vec2 gravity(0.0f, -10.0f);
    bool doSleep = true;

    mWorld = new b2World(gravity, doSleep);

    foreach (Box2DBody *body, mBodies)
        body->initialize(mWorld);

    mTimerId = startTimer(mFrameTime);
}

/**
 * Registers a Box2D body with this world. When the world component is
 * complete, it will initialize the body.
 */
void Box2DWorld::registerBody(Box2DBody *body)
{
    mBodies.append(body);
}

/**
 * Unregisters a Box2D body from this world. It will be asked to clean up after
 * itself.
 */
void Box2DWorld::unregisterBody(Box2DBody *body)
{
    mBodies.removeOne(body);
    body->cleanup(mWorld);
}

void Box2DWorld::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == mTimerId) {
        mWorld->Step(mTimeStep, mVelocityIterations, mPositionIterations);
        mWorld->ClearForces();
        foreach (Box2DBody *body, mBodies)
            body->synchronize();
    }
    QDeclarativeItem::timerEvent(event);
}
