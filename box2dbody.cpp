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
    mBodyDef(),
    mSynchronizing(false),
    mInitializePending(false),
    mGravityScale(1.0)
{
    setTransformOrigin(TopLeft);
    connect(this, SIGNAL(rotationChanged()), SLOT(onRotationChanged()));
}

Box2DBody::~Box2DBody()
{
    cleanup(mWorld);
}

qreal Box2DBody::linearDamping() const
{
    if(mBody) return mBody->GetLinearDamping();
    return mBodyDef.linearDamping;
}

void Box2DBody::setLinearDamping(qreal _linearDamping)
{
    if (linearDamping() == _linearDamping)
        return;
    if (mBody)
        mBody->SetLinearDamping(_linearDamping);
    else
        mBodyDef.linearDamping = _linearDamping;

    emit linearDampingChanged();
}

qreal Box2DBody::angularDamping() const
{
    if(mBody) return mBody->GetAngularDamping();
    return mBodyDef.angularDamping;
}
void Box2DBody::setAngularDamping(qreal _angularDamping)
{
    if (angularDamping() == _angularDamping)
        return;
    if (mBody)
        mBody->SetAngularDamping(_angularDamping);
    else
        mBodyDef.angularDamping = _angularDamping;

    emit angularDampingChanged();
}

Box2DBody::BodyType Box2DBody::bodyType() const
{
    if(mBody) mBody->GetType();
    return static_cast<Box2DBody::BodyType>(mBodyDef.type);
}

void Box2DBody::setBodyType(BodyType _bodyType)
{
    if (bodyType() == _bodyType)
        return;
    if (mBody)
        mBody->SetType(static_cast<b2BodyType>(_bodyType));
    else
        mBodyDef.type = static_cast<b2BodyType>(_bodyType);

    emit bodyTypeChanged();
}

bool Box2DBody::isBullet() const
{
    if(mBody) mBody->IsBullet();
    return mBodyDef.bullet;
}

void Box2DBody::setBullet(bool _bullet)
{
    if (isBullet() == _bullet)
        return;
    if (mBody)
        mBody->SetBullet(_bullet);
    else
        mBodyDef.bullet = _bullet;

    emit bulletChanged();
}

bool Box2DBody::sleepingAllowed() const
{
    if(mBody) mBody->IsSleepingAllowed();
    return mBodyDef.allowSleep;
}

void Box2DBody::setSleepingAllowed(bool allowed)
{
    if (sleepingAllowed() == allowed)
        return;
    if (mBody)
        mBody->SetSleepingAllowed(allowed);
    else
        mBodyDef.allowSleep = allowed;

    emit sleepingAllowedChanged();
}

bool Box2DBody::fixedRotation() const
{
    if(mBody) mBody->IsFixedRotation();
    return mBodyDef.fixedRotation;
}

void Box2DBody::setFixedRotation(bool _fixedRotation)
{
    if (fixedRotation() == _fixedRotation)
        return;
    if (mBody)
        mBody->SetFixedRotation(_fixedRotation);
    else
        mBodyDef.fixedRotation = _fixedRotation;

    emit fixedRotationChanged();
}

bool Box2DBody::active() const
{
    if(mBody) mBody->IsActive();
    return mBodyDef.active;
}

void Box2DBody::setActive(bool _active)
{
    if (active() == _active)
        return;

    if (mBody)
        mBody->SetActive(_active);
    else
        mBodyDef.active = _active;
}

bool Box2DBody::awake() const
{
    if(mBody) mBody->IsAwake();
    return mBodyDef.awake;
}

void Box2DBody::setAwake(bool _awake)
{
    if (awake() == _awake)
        return;

    if (mBody)
        mBody->SetAwake(_awake);
    else
        mBodyDef.awake = _awake;
}

QPointF Box2DBody::linearVelocity() const
{
    b2Vec2 point;
    if(mBody) point = mBody->GetLinearVelocity();
    else point = mBodyDef.linearVelocity;
    return QPointF(point.x * scaleRatio,-point.y * scaleRatio);
}

void Box2DBody::setLinearVelocity(const QPointF &_linearVelocity)
{
    if (linearVelocity() == _linearVelocity)
        return;
    b2Vec2 point(_linearVelocity.x() / scaleRatio,
                                            -_linearVelocity.y() / scaleRatio);
    if (mBody)
        mBody->SetLinearVelocity(point);
    else
        mBodyDef.linearVelocity = point;

    emit linearVelocityChanged();
}

qreal Box2DBody::gravityScale() const
{
    if(mBody) return mBody->GetGravityScale();
    return mGravityScale;
}

void Box2DBody::setGravityScale(qreal _gravityScale)
{
    if(qFuzzyCompare(gravityScale(),_gravityScale))
        return;
    mGravityScale = _gravityScale;
    if(mBody)
    {
        mBody->SetGravityScale(_gravityScale);
        emit gravityScaleChanged();
    }
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

Box2DFixture * Box2DBody::at_fixture(QQmlListProperty<Box2DFixture> *list, int index)
{
    Box2DBody *body = static_cast<Box2DBody*>(list->object);
    if(index < 0 || index >= body->mFixtures.length()) return NULL;
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
    mBodyDef.angle = -(rotation() * (2 * b2_pi)) / 360.0;
    mBody = world->CreateBody(&mBodyDef);
    mInitializePending = false;
    if(mGravityScale != 1.0)
        mBody->SetGravityScale(mGravityScale);
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
    const qreal newRotation = -(angle * 180.0) / b2_pi;

    if (!qFuzzyCompare(x(), newX))
        setX(newX);
    if (!qFuzzyCompare(y(), newY))
        setY(newY);

    if (!qFuzzyCompare(rotation(), newRotation))
        setRotation(newRotation);

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

b2World *Box2DBody::world() const
{
    return mWorld;
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
        return mBody->GetMass() * scaleRatio;
    return 0.0;
}

float Box2DBody::GetInertia() const
{
    if(mBody)
        return mBody->GetInertia();
    return 0.0;
}

QPointF Box2DBody::GetLinearVelocityFromWorldPoint(const QPointF &point)
{
    const b2Vec2 &b2Point = mBody->GetLinearVelocityFromWorldPoint(b2Vec2(point.x() / scaleRatio,
                                                  -point.y() / scaleRatio));
    return QPointF(b2Point.x * scaleRatio,-b2Point.y * scaleRatio);
}

QPointF Box2DBody::GetLinearVelocityFromLocalPoint(const QPointF &point)
{
    const b2Vec2 &b2Point = mBody->GetLinearVelocityFromLocalPoint(b2Vec2(point.x() / scaleRatio,
                                                  -point.y() / scaleRatio));
    return QPointF(b2Point.x * scaleRatio,-b2Point.y * scaleRatio);
}
