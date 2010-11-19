/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the Box2D QML plugin.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2dbody.h"

#include "box2dworld.h"

#include <Box2D.h>
#include <cmath>

static const float scaleRatio = 32.0f; // 32 pixels in one meter

Box2DBody::Box2DBody(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    mBody(0),
    mBodyType(Dynamic),
    mSleepingAllowed(true)
{
}

Box2DBody::~Box2DBody()
{
    if (Box2DWorld *world = qobject_cast<Box2DWorld*>(parent()))
        world->unregisterBody(this);
}

void Box2DBody::setBodyType(BodyType bodyType)
{
    if (mBodyType == bodyType)
        return;

    mBodyType = bodyType;
    if (mBody)
        mBody->SetType(static_cast<b2BodyType>(bodyType));
    emit bodyTypeChanged();
}

void Box2DBody::setSleepingAllowed(bool allowed)
{
    if (mSleepingAllowed == allowed)
        return;

    mSleepingAllowed = allowed;
    if (mBody)
        mBody->SetSleepingAllowed(allowed);
    emit sleepingAllowedChanged();
}

void Box2DBody::componentComplete()
{
    QDeclarativeItem::componentComplete();

    if (Box2DWorld *world = qobject_cast<Box2DWorld*>(parent()))
        world->registerBody(this);
    else
        qWarning() << "Warning: Body should have World as parent";
}

void Box2DBody::initialize(b2World *world)
{
    b2BodyDef bodyDef;
    bodyDef.type = static_cast<b2BodyType>(mBodyType);
    bodyDef.position.Set((x() + width() / 2) / scaleRatio,
                         -(y() + height() / 2) / scaleRatio);
    bodyDef.angle = -(rotation() * (2 * M_PI)) / 360.0;
    bodyDef.allowSleep = mSleepingAllowed;

    mBody = world->CreateBody(&bodyDef);

    // TODO: Create a fixture for each child shape
    b2PolygonShape shape;
    shape.SetAsBox(width() / 2.0f / scaleRatio,
                   height() / 2.0f / scaleRatio);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;    // TODO: Make a property for it in Box2DShape
    fixtureDef.friction = 0.3f;   // TODO: Make a property for it in Box2DShape
    fixtureDef.restitution = 0.5f;

    mBody->CreateFixture(&fixtureDef);
}

/**
 * Synchronizes the state of this body with the internal Box2D state.
 */
void Box2DBody::synchronize()
{
    Q_ASSERT(mBody);
    const b2Vec2 position = mBody->GetPosition();
    const float32 angle = mBody->GetAngle();

    const qreal newX = position.x * scaleRatio - width() / 2;
    const qreal newY = -position.y * scaleRatio - height() / 2;
    const qreal newRotation = -(angle * 360.0) / (2 * M_PI);

    // Do fuzzy comparisions to avoid small inaccuracies causing repaints
    if (!qFuzzyCompare(x(), newX) || !qFuzzyCompare(y(), newY))
        setPos(newX, newY);
    if (!qFuzzyCompare(rotation(), newRotation))
        setRotation(newRotation);
}

void Box2DBody::cleanup(b2World *world)
{
    world->DestroyBody(mBody);
}
