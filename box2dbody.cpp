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

#include "box2dbody.h"

#include "box2dfixture.h"
#include "box2dworld.h"

#include <Box2D.h>
#include <cmath>

Box2DBody::Box2DBody(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    mBody(0),
    mBodyType(Dynamic),
    mSleepingAllowed(true)
{
    setTransformOrigin(TopLeft);
}

Box2DBody::~Box2DBody()
{
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

QDeclarativeListProperty<Box2DFixture> Box2DBody::fixtures()
{
    return QDeclarativeListProperty<Box2DFixture>(this, 0,
                                                  &Box2DBody::append_fixture);
}

void Box2DBody::append_fixture(QDeclarativeListProperty<Box2DFixture> *list,
                               Box2DFixture *fixture)
{
    Box2DBody *body = static_cast<Box2DBody*>(list->object);
    fixture->setParentItem(body);
    body->mFixtures.append(fixture);
}

void Box2DBody::initialize(b2World *world)
{
    b2BodyDef bodyDef;
    bodyDef.type = static_cast<b2BodyType>(mBodyType);
    bodyDef.position.Set(x() / scaleRatio, -y() / scaleRatio);
    bodyDef.angle = -(rotation() * (2 * M_PI)) / 360.0;
    bodyDef.allowSleep = mSleepingAllowed;

    mBody = world->CreateBody(&bodyDef);

    foreach (Box2DFixture *fixture, mFixtures)
        fixture->createFixture(mBody);
}

/**
 * Synchronizes the state of this body with the internal Box2D state.
 */
void Box2DBody::synchronize()
{
    Q_ASSERT(mBody);
    const b2Vec2 position = mBody->GetPosition();
    const float32 angle = mBody->GetAngle();

    const qreal newX = position.x * scaleRatio;
    const qreal newY = -position.y * scaleRatio;
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
    mBody = 0;
}
