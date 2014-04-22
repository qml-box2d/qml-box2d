/*
 * box2dworld.cpp
 * Copyright (c) 2010-2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2012 Adriano Rezende <atdrez@gmail.com>
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

#include "box2dworld.h"

#include "box2dbody.h"
#include "box2dcontact.h"
#include "box2dfixture.h"
#include "box2djoint.h"
#include "box2draycast.h"

StepDriver::StepDriver(Box2DWorld *world)
    : QAbstractAnimation(world)
    , mWorld(world)
{
    setLoopCount(-1); // loop forever
}

int StepDriver::duration() const
{
    return 1000;
}

void StepDriver::updateCurrentTime(int)
{
    mWorld->step();
}


class ContactEvent
{
public:
    enum Type {
        BeginContact,
        EndContact
    };

    Type type;
    Box2DFixture *fixtureA;
    Box2DFixture *fixtureB;
};

class ContactListener : public b2ContactListener
{
public:
    explicit ContactListener(Box2DWorld *world);
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);

    void removeEvent(int index) { mEvents.removeAt(index); }
    void clearEvents() { mEvents.clear(); }
    const QList<ContactEvent> &events() { return mEvents; }

private:
    QList<ContactEvent> mEvents;
    Box2DWorld *mWorld;
    Box2DContact mContact;
};

ContactListener::ContactListener(Box2DWorld *world) :
    mWorld(world)
{
}

void ContactListener::BeginContact(b2Contact *contact)
{
    ContactEvent event;
    event.type = ContactEvent::BeginContact;
    event.fixtureA = toBox2DFixture(contact->GetFixtureA());
    event.fixtureB = toBox2DFixture(contact->GetFixtureB());
    mEvents.append(event);
}

void ContactListener::EndContact(b2Contact *contact)
{
    ContactEvent event;
    event.type = ContactEvent::EndContact;
    event.fixtureA = toBox2DFixture(contact->GetFixtureA());
    event.fixtureB = toBox2DFixture(contact->GetFixtureB());
    mEvents.append(event);
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    Q_UNUSED(oldManifold)
    mContact.setContact(contact);
    emit mWorld->preSolve(&mContact);
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    Q_UNUSED(impulse)
    mContact.setContact(contact);
    emit mWorld->postSolve(&mContact);
}

Box2DWorld::Box2DWorld(QQuickItem *parent) :
    QQuickItem(parent),
    mWorld(b2Vec2(0.0f, -10.0f)),
    mContactListener(new ContactListener(this)),
    mTimeStep(1.0f / 60.0f),
    mVelocityIterations(8),
    mPositionIterations(3),
    mIsRunning(true),
    mStepDriver(new StepDriver(this)),
    mProfile(new Box2DProfile(&mWorld, this)),
    mPixelsPerMeter(32.0f)
{
    mWorld.SetContactListener(mContactListener);
    mWorld.SetDestructionListener(this);
}

Box2DWorld::~Box2DWorld()
{
    // The bodies and joints will be deleted as part of the world, so it's
    // important that they are no longer referenced from the Box2DBody and
    // Box2DJoint instances.
    for (b2Body *body = mWorld.GetBodyList(); body; body = body->GetNext())
        toBox2DBody(body)->nullifyBody();
    for (b2Joint *joint = mWorld.GetJointList(); joint; joint = joint->GetNext())
        toBox2DJoint(joint)->nullifyJoint();

    mWorld.SetContactListener(0);
    delete mContactListener;
}

void Box2DWorld::setTimeStep(float timeStep)
{
    if (mTimeStep != timeStep) {
        mTimeStep = timeStep;
        emit timeStepChanged();
    }
}

void Box2DWorld::setRunning(bool running)
{
    if (mIsRunning == running)
        return;

    mIsRunning = running;
    emit runningChanged();

    if (isComponentComplete()) {
        if (running)
            mStepDriver->start();
        else
            mStepDriver->stop();
    }
}

void Box2DWorld::setVelocityIterations(int iterations)
{
    if (mVelocityIterations != iterations) {
        mVelocityIterations = iterations;
        emit velocityIterationsChanged();
    }
}

void Box2DWorld::setPositionIterations(int iterations)
{
    if (mPositionIterations != iterations) {
        mPositionIterations = iterations;
        emit positionIterationsChanged();
    }
}

QPointF Box2DWorld::gravity() const
{
    return invertY(mWorld.GetGravity());
}

void Box2DWorld::setGravity(const QPointF &gravity)
{
    const b2Vec2 invertedGravity = invertY(gravity);
    if (mWorld.GetGravity() == invertedGravity)
        return;

    mWorld.SetGravity(invertedGravity);
    emit gravityChanged();
}

void Box2DWorld::setAutoClearForces(bool autoClearForces)
{
    if (mWorld.GetAutoClearForces() == autoClearForces)
        return;

    mWorld.SetAutoClearForces(autoClearForces);
    emit autoClearForcesChanged();
}

void Box2DWorld::setPixelsPerMeter(float pixelsPerMeter)
{
    if (pixelsPerMeter <= 0.0f) {
        qWarning("World: pixelsPerMeter must be > 0.0f");
        return;
    }

    if (mPixelsPerMeter != pixelsPerMeter) {
        mPixelsPerMeter = pixelsPerMeter;
        pixelsPerMeterChanged();
    }
}

void Box2DWorld::componentComplete()
{
    QQuickItem::componentComplete();

    initializeBodies(this);

    emit initialized();
    if (mIsRunning)
        mStepDriver->start();
}

void Box2DWorld::SayGoodbye(b2Joint *joint)
{
    if (Box2DJoint *temp = toBox2DJoint(joint)) {
        temp->nullifyJoint();
        delete temp;
    }
}

void Box2DWorld::SayGoodbye(b2Fixture *fixture)
{
    Box2DFixture *f = toBox2DFixture(fixture);

    QList<ContactEvent> events = mContactListener->events();
    for (int i = events.count() - 1; i >= 0; i--) {
        if (events.at(i).fixtureA == f || events.at(i).fixtureB == f)
            mContactListener->removeEvent(i);
    }
}

void Box2DWorld::step()
{
    mWorld.Step(mTimeStep, mVelocityIterations, mPositionIterations);

    for (b2Body *body = mWorld.GetBodyList(); body; body = body->GetNext())
        toBox2DBody(body)->synchronize();

    // Emit contact signals
    foreach (const ContactEvent &event, mContactListener->events()) {
        switch (event.type) {
        case ContactEvent::BeginContact:
            emit event.fixtureA->beginContact(event.fixtureB);
            emit event.fixtureB->beginContact(event.fixtureA);
            break;
        case ContactEvent::EndContact:
            emit event.fixtureA->endContact(event.fixtureB);
            emit event.fixtureB->endContact(event.fixtureA);
            break;
        }
    }
    mContactListener->clearEvents();

    // Emit signals for the current state of the contacts
    b2Contact *contact = mWorld.GetContactList();
    while (contact) {
        Box2DFixture *fixtureA = toBox2DFixture(contact->GetFixtureA());
        Box2DFixture *fixtureB = toBox2DFixture(contact->GetFixtureB());

        emit fixtureA->contactChanged(fixtureB);
        emit fixtureB->contactChanged(fixtureA);

        contact = contact->GetNext();
    }

    emit stepped();
}

void Box2DWorld::rayCast(Box2DRayCast *rayCast,
                         const QPointF &point1,
                         const QPointF &point2)
{
    mWorld.RayCast(rayCast, toMeters(point1), toMeters(point2));
}

void Box2DWorld::itemChange(ItemChange change, const ItemChangeData &value)
{
    if (isComponentComplete()) {
        if (change == ItemChildAddedChange) {
            QObject *child = value.item;
            if (Box2DBody *body = dynamic_cast<Box2DBody*>(child))
                body->initialize(this);
        }
    }

    QQuickItem::itemChange(change, value);
}

void Box2DWorld::initializeBodies(QQuickItem *parent)
{
    foreach (QQuickItem *item, parent->childItems()) {
        if (Box2DBody *body = dynamic_cast<Box2DBody *>(item))
            body->initialize(this);

        initializeBodies(item);
    }
}
