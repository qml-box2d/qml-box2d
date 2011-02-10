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

#include "box2dworld.h"

#include "box2dbody.h"
#include "box2dfixture.h"

#include <QTimerEvent>

#include <Box2D.h>

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
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);

    void clearEvents() { mEvents.clear(); }
    const QList<ContactEvent> &events() { return mEvents; }

private:
    QList<ContactEvent> mEvents;
};

static Box2DFixture *toBox2DFixture(b2Fixture *fixture)
{
    return static_cast<Box2DFixture*>(fixture->GetUserData());
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


Box2DWorld::Box2DWorld(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    mWorld(0),
    mContactListener(new ContactListener),
    mTimeStep(1.0f / 60.0f),
    mVelocityIterations(10),
    mPositionIterations(10),
    mFrameTime(1000 / 60),
    mGravity(qreal(0), qreal(-10)),
    mTimerId(0)
{
}

Box2DWorld::~Box2DWorld()
{
    delete mWorld;
    delete mContactListener;
}

void Box2DWorld::setGravity(const QPointF &gravity)
{
    if (mGravity == gravity)
        return;

    mGravity = gravity;
    if (mWorld)
        mWorld->SetGravity(b2Vec2(gravity.x(), gravity.y()));

    emit gravityChanged();
}

void Box2DWorld::componentComplete()
{
    QDeclarativeItem::componentComplete();

    const b2Vec2 gravity(mGravity.x(), mGravity.y());
    bool doSleep = true;

    mWorld = new b2World(gravity, doSleep);
    mWorld->SetContactListener(mContactListener);

    foreach (QGraphicsItem *child, childItems())
        if (Box2DBody *body = dynamic_cast<Box2DBody*>(child))
            registerBody(body);

    mTimerId = startTimer(mFrameTime);
}

/**
 * Registers a Box2D body with this world. When the world component is
 * complete, it will initialize the body.
 */
void Box2DWorld::registerBody(Box2DBody *body)
{
    mBodies.append(body);
    body->initialize(mWorld);
}

/**
 * Unregisters a Box2D body from this world. It will be asked to clean up after
 * itself.
 */
void Box2DWorld::unregisterBody(Box2DBody *body)
{
    mBodies.removeOne(body);
    body->cleanup(mWorld);
}

void Box2DWorld::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == mTimerId) {
        mWorld->Step(mTimeStep, mVelocityIterations, mPositionIterations);
        foreach (Box2DBody *body, mBodies)
            body->synchronize();

        // Emit contact signals
        foreach (const ContactEvent &event, mContactListener->events()) {
            switch (event.type) {
            case ContactEvent::BeginContact:
                event.fixtureA->emitBeginContact(event.fixtureB);
                event.fixtureB->emitBeginContact(event.fixtureA);
                break;
            case ContactEvent::EndContact:
                event.fixtureA->emitEndContact(event.fixtureB);
                event.fixtureB->emitEndContact(event.fixtureA);
                break;
            }
        }
        mContactListener->clearEvents();

        // Emit signals for the current state of the contacts
        b2Contact *contact = mWorld->GetContactList();
        while (contact) {
            Box2DFixture *fixtureA = toBox2DFixture(contact->GetFixtureA());
            Box2DFixture *fixtureB = toBox2DFixture(contact->GetFixtureB());

            fixtureA->emitContactChanged(fixtureB);
            fixtureB->emitContactChanged(fixtureA);

            contact = contact->GetNext();
        }

        emit stepped();
    }
    QDeclarativeItem::timerEvent(event);
}

QVariant Box2DWorld::itemChange(GraphicsItemChange change,
                                const QVariant &value)
{
    if (isComponentComplete()) {
        if (change == ItemChildAddedChange) {
            QGraphicsItem *child = value.value<QGraphicsItem*>();
            if (Box2DBody *body = dynamic_cast<Box2DBody*>(child))
                registerBody(body);
        } else if (change == ItemChildRemovedChange) {
            QGraphicsItem *child = value.value<QGraphicsItem*>();
            if (Box2DBody *body = dynamic_cast<Box2DBody*>(child))
                unregisterBody(body);
        }
    }

    return QDeclarativeItem::itemChange(change, value);
}
