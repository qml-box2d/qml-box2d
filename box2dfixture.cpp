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

#include "box2dfixture.h"

#include "box2dworld.h"

#include <Box2D.h>

Box2DFixture::Box2DFixture(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    mFixture(0),
    mDensity(0.0f),
    mFriction(0.2f),
    mRestitution(0.0f),
    mSensor(false)
{
}

void Box2DFixture::setDensity(float density)
{
    if (mDensity == density)
        return;

    mDensity = density;
    if (mFixture)
        mFixture->SetDensity(density);
    emit densityChanged();
}

void Box2DFixture::setFriction(float friction)
{
    if (mFriction == friction)
        return;

    mFriction = friction;
    if (mFixture)
        mFixture->SetFriction(friction);
    emit frictionChanged();
}

void Box2DFixture::setRestitution(float restitution)
{
    if (mRestitution == restitution)
        return;

    mRestitution = restitution;
    if (mFixture)
        mFixture->SetRestitution(restitution);
    emit restitutionChanged();
}

void Box2DFixture::setSensor(bool sensor)
{
    if (mSensor == sensor)
        return;

    mSensor = sensor;
    if (mFixture)
        mFixture->SetSensor(sensor);
    emit sensorChanged();
}

void Box2DFixture::createFixture(b2Body *body)
{
    b2Shape *shape = createShape();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = mDensity;
    fixtureDef.friction = mFriction;
    fixtureDef.restitution = mRestitution;
    fixtureDef.isSensor = mSensor;

    mFixture = body->CreateFixture(&fixtureDef);
    mFixture->SetUserData(this);

    delete shape;
}

void Box2DFixture::emitBeginContact(Box2DFixture *other)
{
    emit beginContact(other);
}

void Box2DFixture::emitContactChanged(Box2DFixture *other)
{
    emit contactChanged(other);
}

void Box2DFixture::emitEndContact(Box2DFixture *other)
{
    emit endContact(other);
}


b2Shape *Box2DBox::createShape()
{
    const float32 _x = x() / scaleRatio;
    const float32 _y = -y() / scaleRatio;

    b2Vec2 vertices[4];
    vertices[0].Set(_x, _y);
    vertices[1].Set(_x, _y - height() / scaleRatio);
    vertices[2].Set(_x + width() / scaleRatio, _y - height() / scaleRatio);
    vertices[3].Set(_x + width() / scaleRatio, _y);
    int32 count = 4;

    b2PolygonShape *shape = new b2PolygonShape;
    shape->Set(vertices, count);
    return shape;
}

b2Shape *Box2DCircle::createShape()
{
    b2CircleShape *shape = new b2CircleShape;
    shape->m_radius = mRadius / scaleRatio;
    shape->m_p.Set(x() / scaleRatio, -y() / scaleRatio);
    return shape;
}
