/*
 * box2dworld.h
 * Copyright (c) 2010 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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

#ifndef BOX2DWORLD_H
#define BOX2DWORLD_H

#include <QAbstractAnimation>
#include <QQuickItem>

class Box2DContact;
class Box2DFixture;
class Box2DJoint;
class Box2DWorld;
class ContactListener;
class Box2DDestructionListener;
class StepDriver;

class b2World;

// TODO: Maybe turn this into a property of the world, though it can't be
// changed dynamically.
static const float scaleRatio = 32.0f; // 32 pixels in one meter

/**
 * Small utility class to synchronize the stepping with the framerate.
 */
class StepDriver : public QAbstractAnimation
{
    Q_OBJECT

public:
    explicit StepDriver(Box2DWorld *world);

    int duration() const;

protected:
    void updateCurrentTime(int);

private:
    Box2DWorld *mWorld;
};


/**
 * Wrapper class around a Box2D world.
 */
class Box2DWorld : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(float timeStep READ timeStep WRITE setTimeStep)
    Q_PROPERTY(int velocityIterations READ velocityIterations WRITE setVelocityIterations)
    Q_PROPERTY(int positionIterations READ positionIterations WRITE setPositionIterations)
    Q_PROPERTY(QPointF gravity READ gravity WRITE setGravity NOTIFY gravityChanged)

public:
    explicit Box2DWorld(QQuickItem *parent = 0);
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
     * 8 by default.
     */
    int velocityIterations() const
    { return mVelocityIterations; }

    void setVelocityIterations(int iterations)
    { mVelocityIterations = iterations; }


    /**
     * The number of position iterations used to process one step.
     * 3 by default.
     */
    int positionIterations() const
    { return mPositionIterations; }

    void setPositionIterations(int iterations)
    { mPositionIterations = iterations; }

    QPointF gravity() const { return mGravity; }
    void setGravity(const QPointF &gravity);

    void componentComplete();

    b2World *world() const { return mWorld; }

    void step();

private slots:
    void fixtureDestroyed(Box2DFixture *fixture);

signals:
    void initialized();
    void preSolve(Box2DContact * contact);
    void postSolve(Box2DContact * contact);
    void gravityChanged();
    void runningChanged();
    void stepped();

protected:
    void itemChange(ItemChange, const ItemChangeData &);
    void initializeBodies(QQuickItem *parent);

private:
    b2World *mWorld;
    ContactListener *mContactListener;
    Box2DDestructionListener *mDestructionListener;
    float mTimeStep;
    int mVelocityIterations;
    int mPositionIterations;
    QPointF mGravity;
    bool mIsRunning;
    StepDriver *mStepDriver;
};

QML_DECLARE_TYPE(Box2DWorld)

#endif // BOX2DWORLD_H
