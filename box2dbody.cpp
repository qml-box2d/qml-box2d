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

#include <cmath>

Box2DBody::Box2DBody(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    mBody(0),
    mWorld(0),
    mLinearDamping(0.0f),
    mAngularDamping(0.0f),
    mBodyType(Dynamic),
    mBullet(false),
    mSleepingAllowed(true),
    mFixedRotation(false),
    mActive(true),
    mSynchronizing(false),
    mInitializePending(false)
{
    setTransformOrigin(TopLeft);
    connect(this, SIGNAL(rotationChanged()), SLOT(onRotationChanged()));
}

Box2DBody::~Box2DBody()
{
}

void Box2DBody::setLinearDamping(qreal linearDamping)
{
    if (mLinearDamping == linearDamping)
        return;

    mLinearDamping = linearDamping;
    if (mBody)
        mBody->SetLinearDamping(linearDamping);
    emit linearDampingChanged();
}

void Box2DBody::setAngularDamping(qreal angularDamping)
{
    if (mAngularDamping == angularDamping)
        return;

    mAngularDamping = angularDamping;
    if (mBody)
        mBody->SetAngularDamping(angularDamping);
    emit angularDampingChanged();
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

void Box2DBody::setBullet(bool bullet)
{
    if (mBullet == bullet)
        return;

    mBullet = bullet;
    if (mBody)
        mBody->SetBullet(bullet);
    emit bulletChanged();
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

void Box2DBody::setFixedRotation(bool fixedRotation)
{
    if (mFixedRotation == fixedRotation)
        return;

    mFixedRotation = fixedRotation;
    if (mBody)
        mBody->SetFixedRotation(fixedRotation);
    emit fixedRotationChanged();
}

void Box2DBody::setActive(bool active)
{
    if (mActive == active)
        return;

    mActive = active;
    if (mBody)
        mBody->SetActive(active);
}

void Box2DBody::setLinearVelocity(const QPointF &linearVelocity)
{
    if (mLinearVelocity == linearVelocity)
        return;

    mLinearVelocity = linearVelocity;
    if (mBody)
        mBody->SetLinearVelocity(b2Vec2(mLinearVelocity.x() / scaleRatio,
                                        -mLinearVelocity.y() / scaleRatio));
    emit linearVelocityChanged();
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
    mWorld = world;

    if (!isComponentComplete()) {
        // When components are created dynamically, they get their parent
        // assigned before they have been completely initialized. In that case
        // we need to delay initialization.
        mInitializePending = true;
        return;
    }

    b2BodyDef bodyDef;
    bodyDef.type = static_cast<b2BodyType>(mBodyType);
    bodyDef.position.Set(x() / scaleRatio, -y() / scaleRatio);
    bodyDef.angle = -(rotation() * (2 * M_PI)) / 360.0;
    bodyDef.linearDamping = mLinearDamping;
    bodyDef.angularDamping = mAngularDamping;
    bodyDef.bullet = mBullet;
    bodyDef.allowSleep = mSleepingAllowed;
    bodyDef.fixedRotation = mFixedRotation;

    mBody = world->CreateBody(&bodyDef);
    mInitializePending = false;

    foreach (Box2DFixture *fixture, mFixtures)
        fixture->createFixture(mBody);
}

/**
 * Synchronizes the state of this body with the internal Box2D state.
 */
void Box2DBody::synchronize()
{
    Q_ASSERT(mBody);
    mSynchronizing = true;

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

    b2Vec2 linearVelocity = mBody->GetLinearVelocity();
    setLinearVelocity(QPointF(linearVelocity.x * scaleRatio,
                              -linearVelocity.y * scaleRatio));

    mSynchronizing = false;
}

void Box2DBody::cleanup(b2World *world)
{
    world->DestroyBody(mBody);
    mBody = 0;
    mWorld = 0;
}

void Box2DBody::componentComplete()
{
    QDeclarativeItem::componentComplete();

    if (mInitializePending)
        initialize(mWorld);
}

void Box2DBody::geometryChanged(const QRectF &newGeometry,
                                const QRectF &oldGeometry)
{
    if (!mSynchronizing && mBody) {
        if (newGeometry.topLeft() != oldGeometry.topLeft()) {
            const QPointF pos = newGeometry.topLeft();
            mBody->SetTransform(b2Vec2(pos.x() / scaleRatio,
                                       -pos.y() / scaleRatio),
                                mBody->GetAngle());
        }
    }

    QDeclarativeItem::geometryChanged(newGeometry, oldGeometry);
}

void Box2DBody::onRotationChanged()
{
    if (!mSynchronizing && mBody) {
        mBody->SetTransform(mBody->GetPosition(),
                            (rotation() * 2 * M_PI) / -360.0);
    }
}

void Box2DBody::applyLinearImpulse(const QPointF &impulse,
                                   const QPointF &point)
{
    if (mBody) {
        mBody->ApplyLinearImpulse(b2Vec2(impulse.x() / scaleRatio,
                                         -impulse.y() / scaleRatio),
                                  b2Vec2(point.x() / scaleRatio,
                                         -point.y() / scaleRatio));
    }
}

QPointF Box2DBody::getWorldCenter() const
{
    QPointF worldCenter;
    if (mBody) {
        const b2Vec2 &center = mBody->GetWorldCenter();
        worldCenter.setX(center.x * scaleRatio);
        worldCenter.setY(-center.y * scaleRatio);
    }
    return worldCenter;
}
