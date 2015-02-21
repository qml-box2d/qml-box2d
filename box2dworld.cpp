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

static Box2DWorld * mDefaultWorld;

Box2DWorld::Box2DWorld(QObject *parent) :
    QObject(parent),
    mWorld(b2Vec2(0.0f, -10.0f)),
    mContactListener(0),
    mTimeStep(1.0f / 60.0f),
    mVelocityIterations(8),
    mPositionIterations(3),
    mComponentComplete(false),
    mIsRunning(true),
    mSynchronizing(false),
    mStepDriver(new StepDriver(this)),
    mProfile(new Box2DProfile(&mWorld, this)),
    mEnableContactEvents(true),
    mPixelsPerMeter(32.0f)

{
    mWorld.SetDestructionListener(this);
    if (!mDefaultWorld)
        mDefaultWorld = this;
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
    enableContactListener(false);
    if (mDefaultWorld == this)
        mDefaultWorld = 0;
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

    if (mComponentComplete) {
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

void Box2DWorld::setEnableContactEvents(bool enableContactEvents)
{
    if(enableContactEvents == mEnableContactEvents)
        return;
    mEnableContactEvents = enableContactEvents;
    enableContactListener(mEnableContactEvents);

    emit enableContactEventsChanged();
}

void Box2DWorld::enableContactListener(bool enable)
{
    if (enable) {
        mContactListener = new ContactListener(this);
        mWorld.SetContactListener(mContactListener);
    } else {
        mWorld.SetContactListener(0);
        delete mContactListener;
    }
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

void Box2DWorld::classBegin()
{
}

void Box2DWorld::componentComplete()
{
    mComponentComplete = true;

    enableContactListener(mEnableContactEvents);

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
    if (mEnableContactEvents) {
        Box2DFixture *f = toBox2DFixture(fixture);

        QList<ContactEvent> events = mContactListener->events();
        for (int i = events.count() - 1; i >= 0; i--) {
            if(events.at(i).fixtureA == f || events.at(i).fixtureB == f)
                mContactListener->removeEvent(i);
        }
    }
}

void Box2DWorld::step()
{
    // Update Box2D state before stepping
    for (b2Body *body = mWorld.GetBodyList(); body; body = body->GetNext()) {
        Box2DBody *b = toBox2DBody(body);
        if (b->transformDirty() && b->isActive())
            b->updateTransform();
    }

    mWorld.Step(mTimeStep, mVelocityIterations, mPositionIterations);

    b2Timer timer;

    // Update QML state after stepping
    mSynchronizing = true;
    for (b2Body *body = mWorld.GetBodyList(); body; body = body->GetNext()) {
        Box2DBody *b = toBox2DBody(body);
        if (b->isActive() && b->bodyType() != Box2DBody::Static && b->target())
            b->synchronize();
    }
    mSynchronizing = false;

    mProfile->mSynchronize = timer.GetMilliseconds();
    timer.Reset();

    if (mEnableContactEvents) {
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
    }
    mContactListener->clearEvents();

    mProfile->mEmitSignals = timer.GetMilliseconds();

    emit stepped();
}

void Box2DWorld::rayCast(Box2DRayCast *rayCast,
                         const QPointF &point1,
                         const QPointF &point2)
{
    mWorld.RayCast(rayCast, toMeters(point1), toMeters(point2));
}

Box2DWorld *Box2DWorld::defaultWorld()
{
    return mDefaultWorld;
}
