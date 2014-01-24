/*
 * box2dbody.h
 * Copyright (c) 2010-2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2011 Daker Fernandes Pinheiro <daker.pinheiro@openbossa.org>
 * Copyright (c) 2011 Tan Miaoqing <miaoqing.tan@nokia.com>
 * Copyright (c) 2011 Antonio Aloisio <antonio.aloisio@nokia.com>
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

#ifndef BOX2DBODY_H
#define BOX2DBODY_H

#include <QQuickItem>

class Box2DFixture;
class Box2DWorld;

class b2Body;
class b2World;

/**
 * The Box2D body, build up from a list of shapes.
 */
class Box2DBody : public QQuickItem
{
    Q_OBJECT

    Q_ENUMS(BodyType)
    Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping NOTIFY linearDampingChanged)
    Q_PROPERTY(qreal angularDamping READ angularDamping WRITE setAngularDamping NOTIFY angularDampingChanged)
    Q_PROPERTY(BodyType bodyType READ bodyType WRITE setBodyType NOTIFY bodyTypeChanged)
    Q_PROPERTY(bool bullet READ isBullet WRITE setBullet NOTIFY bulletChanged)
    Q_PROPERTY(bool sleepingAllowed READ sleepingAllowed WRITE setSleepingAllowed NOTIFY sleepingAllowedChanged)
    Q_PROPERTY(bool fixedRotation READ fixedRotation WRITE setFixedRotation NOTIFY fixedRotationChanged)
    Q_PROPERTY(bool active READ active WRITE setActive)
    Q_PROPERTY(QPointF linearVelocity READ linearVelocity WRITE setLinearVelocity NOTIFY linearVelocityChanged)
    Q_PROPERTY(QQmlListProperty<Box2DFixture> fixtures READ fixtures)


public:
    enum BodyType {
        Static,
        Kinematic,
        Dynamic
    };

    explicit Box2DBody(QQuickItem *parent = 0);
    ~Box2DBody();

    qreal linearDamping() const { return mLinearDamping; }
    void setLinearDamping(qreal linearDamping);

    qreal angularDamping() const { return mAngularDamping; }
    void setAngularDamping(qreal angularDamping);

    BodyType bodyType() const { return mBodyType; }
    void setBodyType(BodyType bodyType);

    bool isBullet() const { return mBullet; }
    void setBullet(bool bullet);

    bool sleepingAllowed() const { return mSleepingAllowed; }
    void setSleepingAllowed(bool allowed);

    bool fixedRotation() const { return mFixedRotation; }
    void setFixedRotation(bool fixedRotation);

    bool active() const { return mActive; }
    void setActive(bool active);

    QPointF linearVelocity() const { return mLinearVelocity; }
    void setLinearVelocity(const QPointF &linearVelocity);

    QQmlListProperty<Box2DFixture> fixtures();

    void initialize(b2World *world);
    void synchronize();
    void cleanup(b2World *world);

    Q_INVOKABLE void applyLinearImpulse(const QPointF &impulse,
                                        const QPointF &point);
    Q_INVOKABLE void applyTorque(qreal torque);
    Q_INVOKABLE QPointF getWorldCenter() const;
    Q_INVOKABLE void applyForce(const QPointF &force,
                                        const QPointF &point);
    Q_INVOKABLE float getMass() const;

    void componentComplete();

    b2Body *body() const;

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

signals:
    void linearDampingChanged();
    void angularDampingChanged();
    void bodyTypeChanged();
    void bulletChanged();
    void sleepingAllowedChanged();
    void fixedRotationChanged();
    void linearVelocityChanged();
    void bodyCreated();

private slots:
    void onRotationChanged();

private:
    static void append_fixture(QQmlListProperty<Box2DFixture> *list,
                               Box2DFixture *fixture);

    b2Body *mBody;
    b2World *mWorld;
    qreal mLinearDamping;
    qreal mAngularDamping;
    BodyType mBodyType;
    bool mBullet;
    bool mSleepingAllowed;
    bool mFixedRotation;
    bool mActive;
    QPointF mLinearVelocity;
    bool mSynchronizing;
    bool mInitializePending;
    QList<Box2DFixture*> mFixtures;
};

#endif // BOX2DBODY_H
