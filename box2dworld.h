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

#include <Box2D.h>

class Box2DContact;
class Box2DFixture;
class Box2DJoint;
class Box2DWorld;
class Box2DRayCast;
class ContactListener;
class StepDriver;

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
 * A property group for getting profiling data.
 */
class Box2DProfile : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float step READ step CONSTANT)
    Q_PROPERTY(float collide READ collide CONSTANT)
    Q_PROPERTY(float solve READ solve CONSTANT)
    Q_PROPERTY(float solveInit READ solveInit CONSTANT)
    Q_PROPERTY(float solveVelocity READ solveVelocity CONSTANT)
    Q_PROPERTY(float solvePosition READ solvePosition CONSTANT)
    Q_PROPERTY(float broadphase READ broadphase CONSTANT)
    Q_PROPERTY(float solveTOI READ solveTOI CONSTANT)
    Q_PROPERTY(float synchronize READ synchronize CONSTANT)
    Q_PROPERTY(float emitSignals READ emitSignals CONSTANT)

public:
    explicit Box2DProfile(b2World *world, QObject *parent = 0)
        : QObject(parent)
        , mWorld(world)
    {}

    float step() const;
    float collide() const;
    float solve() const;
    float solveInit() const;
    float solveVelocity() const;
    float solvePosition() const;
    float broadphase() const;
    float solveTOI() const;
    float synchronize() const;
    float emitSignals() const;

private:
    friend class Box2DWorld;

    b2World *mWorld;
    float mSynchronize;
    float mEmitSignals;
};


/**
 * Wrapper class around a Box2D world.
 */
class Box2DWorld : public QObject, public QQmlParserStatus, b2DestructionListener
{
    Q_OBJECT

    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(float timeStep READ timeStep WRITE setTimeStep NOTIFY timeStepChanged)
    Q_PROPERTY(int velocityIterations READ velocityIterations WRITE setVelocityIterations NOTIFY velocityIterationsChanged)
    Q_PROPERTY(int positionIterations READ positionIterations WRITE setPositionIterations NOTIFY positionIterationsChanged)
    Q_PROPERTY(QPointF gravity READ gravity WRITE setGravity NOTIFY gravityChanged)
    Q_PROPERTY(bool autoClearForces READ autoClearForces WRITE setAutoClearForces NOTIFY autoClearForcesChanged)
    Q_PROPERTY(Box2DProfile *profile READ profile NOTIFY stepped)
    Q_PROPERTY(float pixelsPerMeter READ pixelsPerMeter WRITE setPixelsPerMeter NOTIFY pixelsPerMeterChanged)
    Q_PROPERTY(bool enableContactEvents READ enableContactEvents WRITE setEnableContactEvents NOTIFY enableContactEventsChanged)

    Q_INTERFACES(QQmlParserStatus)

public:
    explicit Box2DWorld(QObject *parent = 0);
    ~Box2DWorld();

    float timeStep() const;
    void setTimeStep(float timeStep);

    bool isRunning() const;
    void setRunning(bool running);

    int velocityIterations() const;
    void setVelocityIterations(int iterations);

    int positionIterations() const;
    void setPositionIterations(int iterations);

    QPointF gravity() const;
    void setGravity(const QPointF &gravity);

    bool autoClearForces() const;
    void setAutoClearForces(bool autoClearForces);

    Box2DProfile *profile() const;

    bool enableContactEvents() const;
    void setEnableContactEvents(bool enableContactEvents);

    float pixelsPerMeter() const;
    void setPixelsPerMeter(float pixelsPerMeter);

    float metersPerPixel() const;
    float pixelsPerMeterY() const;
    float metersPerPixelY() const;

    float toPixels(float length) const;
    float toMeters(float length) const;

    QPointF toPixels(const b2Vec2 &vec) const;
    b2Vec2 toMeters(const QPointF &point) const;

    bool isSynchronizing() const;

    void classBegin();
    void componentComplete();

    b2World &world();

    // b2DestructionListener interface
    void SayGoodbye(b2Joint *joint);
    void SayGoodbye(b2Fixture *fixture);

    Q_INVOKABLE void step();
    Q_INVOKABLE void clearForces();
    Q_INVOKABLE void rayCast(Box2DRayCast *rayCast,
                             const QPointF &point1,
                             const QPointF &point2);
    static Box2DWorld * defaultWorld();

signals:
    void preSolve(Box2DContact * contact);
    void postSolve(Box2DContact * contact);

    void timeStepChanged();
    void velocityIterationsChanged();
    void positionIterationsChanged();
    void gravityChanged();
    void autoClearForcesChanged();
    void runningChanged();
    void stepped();
    void enableContactEventsChanged();
    void pixelsPerMeterChanged();

protected:
    void enableContactListener(bool enable);

private:
    b2World mWorld;
    ContactListener *mContactListener;
    float mTimeStep;
    int mVelocityIterations;
    int mPositionIterations;
    bool mComponentComplete;
    bool mIsRunning;
    bool mSynchronizing;
    StepDriver *mStepDriver;
    Box2DProfile *mProfile;
    bool mEnableContactEvents;
    float mPixelsPerMeter;
};


inline float Box2DProfile::step() const
{
    return mWorld->GetProfile().step;
}

inline float Box2DProfile::collide() const
{
    return mWorld->GetProfile().collide;
}

inline float Box2DProfile::solve() const
{
    return mWorld->GetProfile().solve;
}

inline float Box2DProfile::solveInit() const
{
    return mWorld->GetProfile().solveInit;
}

inline float Box2DProfile::solveVelocity() const
{
    return mWorld->GetProfile().solveVelocity;
}

inline float Box2DProfile::solvePosition() const
{
    return mWorld->GetProfile().solvePosition;
}

inline float Box2DProfile::broadphase() const
{
    return mWorld->GetProfile().broadphase;
}

inline float Box2DProfile::solveTOI() const
{
    return mWorld->GetProfile().solveTOI;
}

inline float Box2DProfile::synchronize() const
{
    return mSynchronize;
}

inline float Box2DProfile::emitSignals() const
{
    return mEmitSignals;
}


/**
 * The amount of time to step through each frame in seconds.
 * By default it is 1 / 60.
 */
inline float Box2DWorld::timeStep() const
{
    return mTimeStep;
}

inline bool Box2DWorld::isRunning() const
{
    return mIsRunning;
}

/**
 * The number of velocity iterations used to process one step.
 * 8 by default.
 */
inline int Box2DWorld::velocityIterations() const
{
    return mVelocityIterations;
}

/**
 * The number of position iterations used to process one step.
 * 3 by default.
 */
inline int Box2DWorld::positionIterations() const
{
    return mPositionIterations;
}

inline bool Box2DWorld::autoClearForces() const
{
    return mWorld.GetAutoClearForces();
}

inline Box2DProfile *Box2DWorld::profile() const
{
    return mProfile;
}

inline bool Box2DWorld::enableContactEvents() const
{
    return mEnableContactEvents;
}

inline float Box2DWorld::pixelsPerMeter() const
{
    return mPixelsPerMeter;
}

inline float Box2DWorld::metersPerPixel() const
{
    return 1.0f / pixelsPerMeter();
}

inline float Box2DWorld::pixelsPerMeterY() const
{
    return -pixelsPerMeter(); // Y-axis inverted
}

inline float Box2DWorld::metersPerPixelY() const
{
    return -metersPerPixel();
}

/**
 * Converts lengths from Box2D to QML units.
 */
inline float Box2DWorld::toPixels(float length) const
{
    return length * pixelsPerMeter();
}

/**
 * Converts lengths from QML to Box2D units.
 */
inline float Box2DWorld::toMeters(float length) const
{
    return length * metersPerPixel();
}

/**
 * Converts positions and sizes from Box2D to QML coordinates.
 */
inline QPointF Box2DWorld::toPixels(const b2Vec2 &vec) const
{
    return QPointF(vec.x * pixelsPerMeter(),
                   vec.y * pixelsPerMeterY());
}

/**
 * Converts positions and sizes from QML to Box2D coordinates.
 */
inline b2Vec2 Box2DWorld::toMeters(const QPointF &point) const
{
    return b2Vec2(point.x() * metersPerPixel(),
                  point.y() * metersPerPixelY());
}

inline bool Box2DWorld::isSynchronizing() const
{
    return mSynchronizing;
}

inline b2World &Box2DWorld::world()
{
    return mWorld;
}

inline void Box2DWorld::clearForces()
{
    mWorld.ClearForces();
}


/**
 * Inverts the y-axis as required for forces and velocities.
 */
inline QPointF invertY(const b2Vec2 &vec)
{
    return QPointF(vec.x, -vec.y);
}

/**
 * Inverts the y-axis as required for forces and velocities.
 */
inline b2Vec2 invertY(const QPointF &vec)
{
    return b2Vec2(vec.x(), -vec.y());
}

/**
 * Converts angles from Box2D to QML values.
 */
inline float toDegrees(float radians)
{
    return -radians * 180 / b2_pi;
}

/**
 * Converts angles from QML to Box2D values.
 */
inline float toRadians(float degrees)
{
    return -degrees * b2_pi / 180;
}


QML_DECLARE_TYPE(Box2DWorld)

#endif // BOX2DWORLD_H
