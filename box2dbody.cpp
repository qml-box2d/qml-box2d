/*
 * box2dbody.cpp
 * Copyright (c) 2010-2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2011 Daker Fernandes Pinheiro <daker.pinheiro@openbossa.org>
 * Copyright (c) 2011 Tan Miaoqing <miaoqing.tan@nokia.com>
 * Copyright (c) 2011 Antonio Aloisio <antonio.aloisio@nokia.com>
 * Copyright (c) 2011 Alessandro Portale <alessandro.portale@nokia.com>
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2011 Antti Krats <antti.krats@digia.com>
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

#include "box2dbody.h"

#include "box2dfixture.h"
#include "box2dworld.h"

Box2DBody::Box2DBody(QQuickItem *parent) :
    QQuickItem(parent),
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
    cleanup(mWorld);
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

QQmlListProperty<Box2DFixture> Box2DBody::fixtures()
{
    return QQmlListProperty<Box2DFixture>(this, 0,
                                                  &Box2DBody::append_fixture, 0, 0, 0);
}

void Box2DBody::append_fixture(QQmlListProperty<Box2DFixture> *list,
                               Box2DFixture *fixture)
{
    Box2DBody *body = static_cast<Box2DBody*>(list->object);
    fixture->setParentItem(body);
    body->mFixtures.append(fixture);
}

void Box2DBody::initialize(b2World *world)
{
    mWorld = world;
    //this->setParent(world);
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
    bodyDef.angle = -(rotation() * (2 * b2_pi)) / 360.0;
    bodyDef.linearDamping = mLinearDamping;
    bodyDef.angularDamping = mAngularDamping;
    bodyDef.bullet = mBullet;
    bodyDef.allowSleep = mSleepingAllowed;
    bodyDef.fixedRotation = mFixedRotation;

    mBody = world->CreateBody(&bodyDef);
    mInitializePending = false;

    foreach (Box2DFixture *fixture, mFixtures)
        fixture->createFixture(mBody);
    mBody->SetUserData(this);
    emit bodyCreated();
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
    const qreal newRotation = -(angle * 360.0) / (2 * b2_pi);

    // Do fuzzy comparisions to avoid small inaccuracies causing repaints
    if (!qFuzzyCompare(x(), newX))
        setX(newX);
    if (!qFuzzyCompare(y(), newY))
        setY(newY);

    if (!qFuzzyCompare(rotation(), newRotation))
        setRotation(newRotation);

    b2Vec2 linearVelocity = mBody->GetLinearVelocity();
    setLinearVelocity(QPointF(linearVelocity.x * scaleRatio,
                              -linearVelocity.y * scaleRatio));

    mSynchronizing = false;
}

void Box2DBody::cleanup(b2World *world)
{
    if(mBody) world->DestroyBody(mBody);
    mBody = 0;
    mWorld = 0;
}

void Box2DBody::componentComplete()
{
    QQuickItem::componentComplete();

    if (mInitializePending)
        initialize(mWorld);
}

b2Body *Box2DBody::body() const
{
    return mBody;
}

void Box2DBody::geometryChanged(const QRectF &newGeometry,
                                const QRectF &oldGeometry)
{
    if (!mSynchronizing && mBody) {
        if (newGeometry.x() != oldGeometry.x() || newGeometry.y() != oldGeometry.y())
        {
            mBody->SetTransform(b2Vec2(newGeometry.x() / scaleRatio,-newGeometry.y() / scaleRatio),mBody->GetAngle());
        }
    }
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

void Box2DBody::onRotationChanged()
{
    if (!mSynchronizing && mBody) {
        mBody->SetTransform(mBody->GetPosition(),
                            (rotation() * b2_pi) / -180.0);
    }
}

void Box2DBody::applyLinearImpulse(const QPointF &impulse,
                                   const QPointF &point)
{
    if (mBody) {
        mBody->ApplyLinearImpulse(b2Vec2(impulse.x() / scaleRatio,
                                         -impulse.y() / scaleRatio),
                                  b2Vec2(point.x() / scaleRatio,
                                         -point.y() / scaleRatio),true);
    }
}

void Box2DBody::applyTorque(qreal torque)
{
    if (mBody)
        mBody->ApplyTorque(torque,true);
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

void Box2DBody::applyForce(const QPointF &force, const QPointF &point)
{
    if (mBody) {
        mBody->ApplyForce(b2Vec2(force.x() / scaleRatio,
                                         -force.y() / scaleRatio),
                                  b2Vec2(point.x() / scaleRatio,
                                         -point.y() / scaleRatio),true);
    }
}

float Box2DBody::getMass() const
{
    if (mBody)
        return mBody->GetMass() / scaleRatio;
    return 0.0;
}

