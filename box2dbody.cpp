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
    mSynchronizing(false),
    mInitializePending(false)
{
    mBodyDef.userData = this;

    setTransformOrigin(TopLeft);
    connect(this, SIGNAL(rotationChanged()), SLOT(onRotationChanged()));
}

Box2DBody::~Box2DBody()
{
    if (mBody)
        mWorld->DestroyBody(mBody);
}

void Box2DBody::setLinearDamping(float linearDamping)
{
    if (mBodyDef.linearDamping == linearDamping)
        return;

    mBodyDef.linearDamping = linearDamping;
    if (mBody)
        mBody->SetLinearDamping(linearDamping);

    emit linearDampingChanged();
}

void Box2DBody::setAngularDamping(float angularDamping)
{
    if (mBodyDef.angularDamping == angularDamping)
        return;

    mBodyDef.angularDamping = angularDamping;
    if (mBody)
        mBody->SetAngularDamping(angularDamping);

    emit angularDampingChanged();
}

void Box2DBody::setBodyType(BodyType bodyType)
{
    if (mBodyDef.type == static_cast<b2BodyType>(bodyType))
        return;

    mBodyDef.type = static_cast<b2BodyType>(bodyType);
    if (mBody)
        mBody->SetType(mBodyDef.type);

    emit bodyTypeChanged();
}

void Box2DBody::setBullet(bool bullet)
{
    if (mBodyDef.bullet == bullet)
        return;

    mBodyDef.bullet = bullet;
    if (mBody)
        mBody->SetBullet(bullet);

    emit bulletChanged();
}

void Box2DBody::setSleepingAllowed(bool sleepingAllowed)
{
    if (mBodyDef.allowSleep == sleepingAllowed)
        return;

    mBodyDef.allowSleep = sleepingAllowed;
    if (mBody)
        mBody->SetSleepingAllowed(sleepingAllowed);

    emit sleepingAllowedChanged();
}

void Box2DBody::setFixedRotation(bool fixedRotation)
{
    if (mBodyDef.fixedRotation == fixedRotation)
        return;

    mBodyDef.fixedRotation = fixedRotation;
    if (mBody)
        mBody->SetFixedRotation(fixedRotation);

    emit fixedRotationChanged();
}

void Box2DBody::setActive(bool active)
{
    if (mBodyDef.active == active)
        return;

    mBodyDef.active = active;
    if (mBody)
        mBody->SetActive(active);
}

bool Box2DBody::isAwake() const
{
    return mBody ? mBody->IsAwake() : mBodyDef.awake;
}

void Box2DBody::setAwake(bool awake)
{
    mBodyDef.awake = awake;
    if (mBody)
        mBody->SetAwake(awake);
}

QPointF Box2DBody::linearVelocity() const
{
    b2Vec2 point;
    if (mBody)
        point = mBody->GetLinearVelocity();
    else
        point = mBodyDef.linearVelocity;
    return QPointF(point.x * scaleRatio, -point.y * scaleRatio);
}

void Box2DBody::setLinearVelocity(const QPointF &velocity)
{
    if (linearVelocity() == velocity)
        return;

    mBodyDef.linearVelocity = b2Vec2(velocity.x() / scaleRatio,
                                     -velocity.y() / scaleRatio);
    if (mBody)
        mBody->SetLinearVelocity(mBodyDef.linearVelocity);

    emit linearVelocityChanged();
}

float Box2DBody::angularVelocity() const
{
    float velocity;
    if (mBody)
        velocity = mBody->GetAngularVelocity();
    else
        velocity = mBodyDef.angularVelocity;
    return -velocity * 180 / b2_pi;
}

void Box2DBody::setAngularVelocity(float velocity)
{
    if (angularVelocity() == velocity)
        return;

    mBodyDef.angularVelocity = -velocity * (b2_pi / 180);
    if (mBody)
        mBody->SetAngularVelocity(mBodyDef.angularVelocity);

    emit angularVelocityChanged();
}

void Box2DBody::setGravityScale(float gravityScale)
{
    if (mBodyDef.gravityScale == gravityScale)
        return;

    mBodyDef.gravityScale = gravityScale;
    if (mBody)
        mBody->SetGravityScale(gravityScale);

    emit gravityScaleChanged();
}

QQmlListProperty<Box2DFixture> Box2DBody::fixtures()
{
    return QQmlListProperty<Box2DFixture>(this, 0,
                                          &Box2DBody::append_fixture,
                                          &Box2DBody::count_fixture,
                                          &Box2DBody::at_fixture,
                                          0);
}

void Box2DBody::append_fixture(QQmlListProperty<Box2DFixture> *list,
                               Box2DFixture *fixture)
{
    Box2DBody *body = static_cast<Box2DBody*>(list->object);
    fixture->setParentItem(body);
    body->mFixtures.append(fixture);
}

int Box2DBody::count_fixture(QQmlListProperty<Box2DFixture> *list)
{
    Box2DBody *body = static_cast<Box2DBody*>(list->object);
    return body->mFixtures.length();
}

Box2DFixture *Box2DBody::at_fixture(QQmlListProperty<Box2DFixture> *list, int index)
{
    Box2DBody *body = static_cast<Box2DBody*>(list->object);
    return body->mFixtures.at(index);
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
    mBodyDef.position.Set(x() / scaleRatio, -y() / scaleRatio);
    mBodyDef.angle = rotation() * b2_pi / -180;
    mBody = world->CreateBody(&mBodyDef);
    mInitializePending = false;
    foreach (Box2DFixture *fixture, mFixtures)
        fixture->createFixture(mBody);
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
    const qreal newRotation = -(angle * 180.0) / b2_pi;

    bool xChanged = false;
    bool yChanged = false;

    if (!qFuzzyCompare(x(), newX)) {
        setX(newX);
        xChanged = true;
    }

    if (!qFuzzyCompare(y(), newY)) {
        setY(newY);
        yChanged = true;
    }

    if (xChanged || yChanged)
        emit positionChanged(QPointF(newX, newY));

    if (!qFuzzyCompare(rotation(), newRotation))
        setRotation(newRotation);

    mSynchronizing = false;
}

void Box2DBody::componentComplete()
{
    QQuickItem::componentComplete();

    if (mInitializePending)
        initialize(mWorld);
}

void Box2DBody::geometryChanged(const QRectF &newGeometry,
                                const QRectF &oldGeometry)
{
    if (!mSynchronizing && mBody) {
        if (newGeometry.x() != oldGeometry.x() || newGeometry.y() != oldGeometry.y()) {
            mBody->SetTransform(b2Vec2(newGeometry.x() / scaleRatio,
                                       -newGeometry.y() / scaleRatio),
                                mBody->GetAngle());
        }
    }
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

void Box2DBody::onRotationChanged()
{
    if (!mSynchronizing && mBody) {
        mBody->SetTransform(mBody->GetPosition(),
                            rotation() * b2_pi / -180.0);
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
                                 -point.y() / scaleRatio), true);
    }
}

float Box2DBody::getMass() const
{
    return mBody ? mBody->GetMass() * scaleRatio * scaleRatio : 0.0;
}

void Box2DBody::resetMassData()
{
    if (mBody)
        mBody->ResetMassData();
}

float Box2DBody::getInertia() const
{
    return mBody ? mBody->GetInertia() : 0.0;
}

QPointF Box2DBody::getLinearVelocityFromWorldPoint(const QPointF &point) const
{
    const b2Vec2 b2Point = mBody->GetLinearVelocityFromWorldPoint(b2Vec2(point.x() / scaleRatio,
                                                                         -point.y() / scaleRatio));
    return QPointF(b2Point.x * scaleRatio,
                   -b2Point.y * scaleRatio);
}

QPointF Box2DBody::getLinearVelocityFromLocalPoint(const QPointF &point) const
{
    const b2Vec2 b2Point = mBody->GetLinearVelocityFromLocalPoint(b2Vec2(point.x() / scaleRatio,
                                                                         -point.y() / scaleRatio));
    return QPointF(b2Point.x * scaleRatio,
                   -b2Point.y * scaleRatio);
}
