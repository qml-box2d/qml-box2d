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
#include <Box2D.h>

class Box2DFixture;
class Box2DWorld;

class b2Body;
class b2BodyDef;
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
    Q_PROPERTY(bool awake READ awake WRITE setAwake)
    Q_PROPERTY(QPointF linearVelocity READ linearVelocity WRITE setLinearVelocity NOTIFY linearVelocityChanged)
    Q_PROPERTY(QQmlListProperty<Box2DFixture> fixtures READ fixtures)
    Q_PROPERTY(qreal gravityScale READ gravityScale WRITE setGravityScale NOTIFY gravityScaleChanged)

public:
    enum BodyType {
        Static = 0,
        Kinematic,
        Dynamic
    };

    explicit Box2DBody(QQuickItem *parent = 0);
    ~Box2DBody();

    qreal linearDamping() const;
    void setLinearDamping(qreal _linearDamping);

    qreal angularDamping() const;
    void setAngularDamping(qreal _angularDamping);

    BodyType bodyType() const;
    void setBodyType(BodyType _bodyType);

    bool isBullet() const;
    void setBullet(bool _bullet);

    bool sleepingAllowed() const;
    void setSleepingAllowed(bool allowed);

    bool fixedRotation() const;
    void setFixedRotation(bool _fixedRotation);

    bool active() const;
    void setActive(bool _active);

    bool awake() const;
    void setAwake(bool _awake);

    QPointF linearVelocity() const;
    void setLinearVelocity(const QPointF &_linearVelocity);

    qreal gravityScale() const;
    void setGravityScale(qreal _gravityScale);

    QQmlListProperty<Box2DFixture> fixtures();

    void initialize(b2World *world);
    void synchronize();
    void cleanup(b2World *world);

    Q_INVOKABLE void applyForce(const QPointF &force,const QPointF &point);
    Q_INVOKABLE void applyTorque(qreal torque);
    Q_INVOKABLE void applyLinearImpulse(const QPointF &impulse, const QPointF &point);
    Q_INVOKABLE QPointF getWorldCenter() const;
    Q_INVOKABLE float getMass() const;
    Q_INVOKABLE float GetInertia() const;
    Q_INVOKABLE QPointF GetLinearVelocityFromWorldPoint(const QPointF &point);
    Q_INVOKABLE QPointF GetLinearVelocityFromLocalPoint (const QPointF &point);

    void componentComplete();
    b2Body *body() const;
    b2World * world() const;

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
    void gravityScaleChanged();

private slots:
    void onRotationChanged();

private:
    b2Body *mBody;
    b2World *mWorld;
    b2BodyDef mBodyDef;
    bool mSynchronizing;
    bool mInitializePending;
    QList<Box2DFixture*> mFixtures;

    static void append_fixture(QQmlListProperty<Box2DFixture> *list,
                               Box2DFixture *fixture);
    static int count_fixture(QQmlListProperty<Box2DFixture> *list);
    static Box2DFixture * at_fixture(QQmlListProperty<Box2DFixture> *list,int index);
    qreal mGravityScale;

};

#endif // BOX2DBODY_H
