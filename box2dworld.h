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

#ifndef BOX2DWORLD_H
#define BOX2DWORLD_H

#include <QDeclarativeItem>
#include <QList>
#include <QBasicTimer>

class Box2DBody;
class Box2DFixture;
class Box2DJoint;
class ContactListener;
class Box2DDestructionListener;

class b2World;

// TODO: Maybe turn this into a property of the world, though it can't be
// changed dynamically.
static const float scaleRatio = 32.0f; // 32 pixels in one meter

/**
 * Wrapper class around a Box2D world.
 */
class Box2DWorld : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(float timeStep READ timeStep WRITE setTimeStep)
    Q_PROPERTY(int velocityIterations READ velocityIterations WRITE setVelocityIterations)
    Q_PROPERTY(int positionIterations READ positionIterations WRITE setPositionIterations)
    Q_PROPERTY(int frameTime READ frameTime WRITE setFrameTime)
    Q_PROPERTY(QPointF gravity READ gravity WRITE setGravity NOTIFY gravityChanged)

public:
    explicit Box2DWorld(QDeclarativeItem *parent = 0);
    ~Box2DWorld();

    /**
     * The amount of time to step through each frame in seconds.
     * By default it is 1 / 60.
     */
    float timeStep() const { return mTimeStep; }
    void setTimeStep(float timeStep) { mTimeStep = timeStep; }

    bool isRunning() const { return mIsRunning; }
    void setRunning(bool running);

    /**
     * The number of velocity iterations used to process one step.
     * 10 by default.
     */
    int velocityIterations() const
    { return mVelocityIterations; }

    void setVelocityIterations(int iterations)
    { mVelocityIterations = iterations; }


    /**
     * The number of position iterations used to process one step.
     * 10 by default.
     */
    int positionIterations() const
    { return mPositionIterations; }

    void setPositionIterations(int iterations)
    { mPositionIterations = iterations; }

    /**
     * The amount of time each frame takes in milliseconds.
     * By default it is 1000 / 60.
     */
    int frameTime() const { return mFrameTime; }
    void setFrameTime(int frameTime) { mFrameTime = frameTime; }

    QPointF gravity() const { return mGravity; }
    void setGravity(const QPointF &gravity);

    void componentComplete();

    void registerBody(Box2DBody *body);

    b2World *world() const { return mWorld; }

private slots:
    void unregisterBody();
    void fixtureDestroyed(Box2DFixture *fixture);

signals:
    void gravityChanged();
    void runningChanged();
    void stepped();

protected:
    void timerEvent(QTimerEvent *);
    QVariant itemChange(GraphicsItemChange, const QVariant &);

private:
    b2World *mWorld;
    ContactListener *mContactListener;
    Box2DDestructionListener *mDestructionListener;
    float mTimeStep;
    int mVelocityIterations;
    int mPositionIterations;
    int mFrameTime;
    QPointF mGravity;
    bool mIsRunning;
    QBasicTimer mTimer;
    QList<Box2DBody*> mBodies;
};

QML_DECLARE_TYPE(Box2DWorld)

#endif // BOX2DWORLD_H
