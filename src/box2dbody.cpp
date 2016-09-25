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
#include <qmath.h>





static bool sync(float &value, float newValue)
{
    if (qFuzzyCompare(value, newValue))
        return false;

    value = newValue;
    return true;
}

static bool sync(b2Vec2 &value, const b2Vec2 &newValue)
{
    if (qFuzzyCompare(value.x, newValue.x) && qFuzzyCompare(value.y, newValue.y))
        return false;

    value = newValue;
    return true;
}



/*!
   \qmltype Body
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject QQmlParserStatus
   \brief  Bodies have position and velocity. You can apply forces, torques,
and impulses to bodies. Bodies can be static, kinematic, or dynamic.


*/






/*!
\qmlproperty real Body::angularDamping

Damping is used to reduce the world velocity of bodies. Damping is different than friction because
friction only occurs with contact. Damping is not a replacement for friction and the two effects should
be used together.
Damping parameters should be between

0.0 and infinity, with 0 meaning no damping, and infinity
meaning full damping.

Normally you will use a damping value between 0.1 and 1. I generally do not use
linear damping because it makes bodies look like they are floating.
\code
    Body{
        angularDamping = 0.1
    }
\endcode

Damping is approximated for stability and performance. At small damping values the damping effect is
mostly independent of the time step. At larger damping values, the damping effect will vary with the
time step. This is not an issue if you use a fixed time step (recommended).
 */











/*!
 * \qmlproperty enum Body::bodyType
There are 3 Differrnt bodytypes. each of them do sperate things.
    \table
        \row
            \li Body.Static
    \endtable
A static body does not move under simulation and behaves as if it has infinite mass. Internally, Box2D
stores zero for the mass and the inverse mass. Static bodies can be moved manually by the user. A static
body has zero velocity. Static bodies do not collide with other static or kinematic bodies.
    \table
        \row
            \li Body.Kinematic
    \endtable
A kinematic body moves under simulation according to its velocity. Kinematic bodies do not respond to
forces. They can be moved manually by the user, but normally a kinematic body is moved by setting its
velocity. A kinematic body behaves as if it has infinite mass, however, Box2D stores zero for the mass
and the inverse mass. Kinematic bodies do not collide with other kinematic or static bodies.
    \table
        \row
            \li Body.Dynamic
    \endtable
A dynamic body is fully simulated. They can be moved manually by the user, but normally they move
according to forces. A dynamic body can collide with all body types. A dynamic body always has finite,
non-zero mass. If you try to set the mass of a dynamic body to zero, it will automatically acquire a mass
of one kilogram and it won’t rotate.
Bodies are the backbone for Fixture (shapes). {Body} {Bodies} carry Fixture and move them around in the World.
Bodies are always rigid bodies in Box2D. That means that two {Ficture}{fixtures} attached to the same rigid body
never move relative to each other and fixtures attached to the same body don’t collide.
 */









/*!
\qmlproperty bool Body::bullet
Game simulation usually generates a sequence of images that are played at some frame rate. This is
called discrete simulation. In discrete simulation, rigid bodies can move by a large amount in one time step.
If a physics engine doesn't account for the large motion, you may see some objects incorrectly pass
through each other. This effect is called tunneling.
By default, Box2D uses continuous collision detection (CCD) to prevent dynamic bodies from tunneling
through static bodies. This is done by sweeping shapes from their old position to their new positions.
The engine looks for new collisions during the sweep and computes the time of impact (TOI) for these
collisions. Bodies are moved to their first TOI and then the solver performs a sub-step to complete the
full time step. There may be additional TOI events within a sub-step.
Normally CCD is not used between dynamic bodies. This is done to keep performance reasonable. In
some game scenarios you need dynamic bodies to use CCD. For example, you may want to shoot a high
speed bullet at a stack of dynamic bricks. Without CCD, the bullet might tunnel through the bricks.
Fast moving objects in Box2D can be labeled as bullets. Bullets will perform CCD with both static and
dynamic bodies. You should decide what bodies should be bullets based on your game design. If you
decide a body should be treated as a bullet, use the following setting.
    \code
        bullet = true;
    \endcode

The bullet flag only affects dynamic bodies.
*/








/*!
\qmlproperty bool Body::sleepingAllowed
Boolean property that allows one to put the body to sleep.
What does sleep mean?
Well it is expensive to simulate bodies, so the less we have to simulate the
better. When a body comes to rest we would like to stop simulating it.
When Box2D determines that a Body (or group of bodies see Fixture) has come to rest,
the body enters a sleep state which has very little CPU overhead. If a Body is awake and
collides with a sleeping Body, then the sleeping body wakes up. Bodies will also wake up
if a Joint or contact attached to them is destroyed.
You can also wake a body manually. The Body definition lets you specify whether a Body
can sleep and whether a Body is created sleeping.
    \code
        Body{
            id: sleepyBody
            sleepingTrue = true
    }
    \endcode
*/




/*!
  \qmlproperty bool Body::fixedRotation
You may want a rigid Body, such as a character, to have a fixed rotation.

Such a Body should not rotate, even under load.
You can use the fixedRotation setting to achieve this:
\code
        Body{
                id:fixedBody
                fixedRotation = true
         }
\endcode
 */



/*!
  \qmlproperty  bool  Body::active
You may wish a body to be created but not participate in collision or dynamics.
This state is similar to {sleepingAllowed} {sleeping} except the body will not be woken
by other bodies and the body's {Fixture}{fixtures} will not be placed in the broad-phase.
This means the body will not participate in collisions,  etc. You can create a Body in an
inactive state and later re-activate it.
    \code
            Body{
                id: naBody
                active = true
                fixture:
                ...
                ........
                .............
                }
                Button{
                        anchor.fill: parent
                        onClicked{ na.active = false}
            }
    \endcode

{Joint} {Joints} may be connected to inactive bodies. These {Joint} {joints} will not be simulated.
You should be careful when you activate a Body that its {Joint} {joints} are not distorted.
Note that activating a body is almost as expensive as creating the body from scratch.
*/




/*!
  \qmlproperty bool Body::awake
  see sleepAllowed
 */


/*!
 \qmlproperty QQmlListProperty Body::fixtures
 a list of elements that will be attached to the Body. This can be a single element or many.

 */

Box2DBody::Box2DBody(QObject *parent) :
    QObject(parent),
    mWorld(0),
    mTarget(0),
    mBody(0),
    mComponentComplete(false),
    mTransformDirty(false),
    mCreatePending(false)
{
    mBodyDef.userData = this;
    setWorld(Box2DWorld::defaultWorld());
}

Box2DBody::~Box2DBody()
{
    if (mBody)
        mWorld->world().DestroyBody(mBody);
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
    if (mBody)
        return invertY(mBody->GetLinearVelocity());
    return invertY(mBodyDef.linearVelocity);
}

void Box2DBody::setLinearVelocity(const QPointF &velocity)
{
    if (linearVelocity() == velocity)
        return;

    mBodyDef.linearVelocity = invertY(velocity);
    if (mBody)
        mBody->SetLinearVelocity(mBodyDef.linearVelocity);

    emit linearVelocityChanged();
}

float Box2DBody::angularVelocity() const
{
    if (mBody)
        return toDegrees(mBody->GetAngularVelocity());
    return toDegrees(mBodyDef.angularVelocity);
}

void Box2DBody::setAngularVelocity(float velocity)
{
    if (angularVelocity() == velocity)
        return;

    mBodyDef.angularVelocity = toRadians(velocity);
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

QPointF Box2DBody::originOffset() const
{
    Q_ASSERT(mTarget);

    QPointF origin = -mTarget->transformOriginPoint();
    qreal c = qCos(-mBodyDef.angle);
    qreal s = qSin(-mBodyDef.angle);

    return QPointF(origin.x() * c - origin.y() * s - origin.x(),
                   origin.x() * s + origin.y() * c - origin.y());
}

/*!
\qmlmethod void Body::addFixture(Item fixture)
 */
void Box2DBody::addFixture(Box2DFixture *fixture)
{
    mFixtures.append(fixture);
    if (mBody)
        fixture->initialize(this);
}

void Box2DBody::createBody()
{
    if (!mWorld)
        return;

    if (!mComponentComplete) {
        // When components are created dynamically, they get their parent
        // assigned before they have been completely initialized. In that case
        // we need to delay initialization.
        mCreatePending = true;
        return;
    }

    if (!mTarget)
        mTarget = qobject_cast<QQuickItem *>(parent());

    if (mTarget) {
        mBodyDef.angle = toRadians(mTarget->rotation());
        mBodyDef.position = mWorld->toMeters(
                    mTarget->transformOrigin() == QQuickItem::TopLeft ?
                        mTarget->position() :
                        mTarget->position() + originOffset());
    }

    mBody = mWorld->world().CreateBody(&mBodyDef);
    mCreatePending = false;
    mTransformDirty = false;
    foreach (Box2DFixture *fixture, mFixtures)
        fixture->initialize(this);
    emit bodyCreated();
}

/**
 * Synchronizes the state of this body with the internal Box2D state.
 */
void Box2DBody::synchronize()
{
    Q_ASSERT(mBody);

    if (sync(mBodyDef.angle, mBody->GetAngle()))
        if (mTarget)
            mTarget->setRotation(toDegrees(mBodyDef.angle));

    if (sync(mBodyDef.position, mBody->GetPosition())) {
        if (mTarget) {
            mTarget->setPosition(
                        mTarget->transformOrigin() == QQuickItem::TopLeft ?
                            mWorld->toPixels(mBodyDef.position) :
                            mWorld->toPixels(mBodyDef.position) - originOffset());

        }
        emit positionChanged();
    }
}

void Box2DBody::classBegin()
{
}

void Box2DBody::componentComplete()
{
    mComponentComplete = true;

    if (mCreatePending)
        createBody();
}

void Box2DBody::setWorld(Box2DWorld *world)
{
    if (mWorld == world)
        return;

    if (mWorld)
        disconnect(mWorld, SIGNAL(pixelsPerMeterChanged()), this, SLOT(onWorldPixelsPerMeterChanged()));
    if (world)
        connect(world, SIGNAL(pixelsPerMeterChanged()), this, SLOT(onWorldPixelsPerMeterChanged()));

    // Destroy body when leaving our previous world
    if (mWorld && mBody) {
        mWorld->world().DestroyBody(mBody);
        mBody = 0;
    }

    mWorld = world;
    createBody();
}

void Box2DBody::setTarget(QQuickItem *target)
{
    if (mTarget == target)
        return;

    if (mTarget)
        mTarget->disconnect(this);

    mTarget = target;
    mTransformDirty = target != 0;

    if (target) {
        connect(target, SIGNAL(xChanged()), this, SLOT(markTransformDirty()));
        connect(target, SIGNAL(yChanged()), this, SLOT(markTransformDirty()));
        connect(target, SIGNAL(rotationChanged()), this, SLOT(markTransformDirty()));
    }

    emit targetChanged();
}

void Box2DBody::updateTransform()
{
    Q_ASSERT(mTarget);
    Q_ASSERT(mBody);
    Q_ASSERT(mTransformDirty);

    mBodyDef.angle = toRadians(mTarget->rotation());
    mBodyDef.position = mWorld->toMeters(
                mTarget->transformOrigin() == QQuickItem::TopLeft ?
                    mTarget->position() :
                    mTarget->position() + originOffset());

    mBody->SetTransform(mBodyDef.position, mBodyDef.angle);
    mTransformDirty = false;
}

/*!
 \qmlmethod Body::applyLinearImpulse(point impulse, point point)

*/
void Box2DBody::applyLinearImpulse(const QPointF &impulse,
                                   const QPointF &point)
{
    if (mBody)
        mBody->ApplyLinearImpulse(invertY(impulse), mWorld->toMeters(point), true);
}

/*!
 \qmlmethod Body::applyAngularImpulse(real impulse)
 */
void Box2DBody::applyAngularImpulse(qreal impulse)
{
    if (mBody)
        mBody->ApplyAngularImpulse(impulse, true);
}

/*!
 \qmlmethod Body::applyTorque(real torque)
 */
void Box2DBody::applyTorque(qreal torque)
{
    if (mBody)
        mBody->ApplyTorque(torque, true);
}

/*!
 \qmlmethod Body::getWorldCenter()
    returns a Qt.point of the center of the Box2d World

    \sa World
*/
QPointF Box2DBody::getWorldCenter() const
{
    if (mBody)
        return mWorld->toPixels(mBody->GetWorldCenter());
    return QPointF();
}

/*!
 \qmlmethod Body::getLocalCenter()
 */
QPointF Box2DBody::getLocalCenter() const
{
    if (mBody)
        return mWorld->toPixels(mBody->GetLocalCenter());
    return QPointF();
}

/*!
  \qmlmethod Body::applyForce(QPointF force, QPointF point)

*/
void Box2DBody::applyForce(const QPointF &force, const QPointF &point)
{
    if (mBody)
        mBody->ApplyForce(invertY(force), mWorld->toMeters(point), true);
}

/*!
 \qmlmethod Body::applyForceToCenter(point force)
 */
void Box2DBody::applyForceToCenter(const QPointF &force)
{
    if (mBody)
        mBody->ApplyForceToCenter(invertY(force), true);
}

/*!
\qmlmethod float Body::getMass()
 */
float Box2DBody::getMass() const
{
    return mBody ? mBody->GetMass() : 0.0;
}

/*!
 \qmlmethod void Body::resetMassData()
 */
void Box2DBody::resetMassData()
{
    if (mBody)
        mBody->ResetMassData();
}

/*!
 \qmlmethod float Body::getInertia()
 */
float Box2DBody::getInertia() const
{
    return mBody ? mBody->GetInertia() : 0.0;
}

/*!
 \qmlmethod Body::toWorldPoint(QPointF localPoint)
 */
QPointF Box2DBody::toWorldPoint(const QPointF &localPoint) const
{
    if (mBody)
        return mWorld->toPixels(mBody->GetWorldPoint(mWorld->toMeters(localPoint)));
    return QPointF();
}

/*!
 \qmlmethod  Body::toWorldVector(QPointF localVector)
 */
QPointF Box2DBody::toWorldVector(const QPointF &localVector) const
{
    if (mBody)
        return mWorld->toPixels(mBody->GetWorldVector(mWorld->toMeters(localVector)));
    return QPointF();
}

/*!
 \qmlmethod Body::toLocalPoint(QPointF worldPoint)
 */
QPointF Box2DBody::toLocalPoint(const QPointF &worldPoint) const
{
    if (mBody)
        return mWorld->toPixels(mBody->GetLocalPoint(mWorld->toMeters(worldPoint)));
    return QPointF();
}

/*!
\qmlmethod Qt.point Body::toLocalVector(QPointF worldVector)
 */
QPointF Box2DBody::toLocalVector(const QPointF &worldVector) const
{
    if (mBody)
        return mWorld->toPixels(mBody->GetLocalVector(mWorld->toMeters(worldVector)));
    return QPointF();
}

/*!
\qmlmethod Qt.point Body::getLinearVelocityFromWorldPoint(QPointF point)
 */
QPointF Box2DBody::getLinearVelocityFromWorldPoint(const QPointF &point) const
{
    if (mBody)
        return invertY(mBody->GetLinearVelocityFromWorldPoint(mWorld->toMeters(point)));
    return QPointF();
}

/*!
 \qmlmethod Qt.point Body::getLinearVelocityFromLocalPoint(QPointF point)
 */
QPointF Box2DBody::getLinearVelocityFromLocalPoint(const QPointF &point) const
{
    if (mBody)
        return invertY(mBody->GetLinearVelocityFromLocalPoint(mWorld->toMeters(point)));
    return QPointF();
}

void Box2DBody::markTransformDirty()
{
    mTransformDirty = mTransformDirty || (mWorld && !mWorld->isSynchronizing());
}

void Box2DBody::onWorldPixelsPerMeterChanged()
{
    if (mBody) {
        foreach (Box2DFixture *fixture, mFixtures)
            fixture->recreateFixture();
        markTransformDirty();
        updateTransform();
    }
}
