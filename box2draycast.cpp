/*
 * box2draycast.cpp
 * Copyright (c) 2014 Moukhlynin Ruslan <ruslan@khvmntk.ru>
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

#include "box2draycast.h"

#include "box2dworld.h"
#include "box2dfixture.h"


Box2DRayCast::Box2DRayCast(QObject *parent) :
    QObject(parent),
    mComponentComplete(false),
    mPoint1(0,0),
    mPoint2(0,0),
    mRepeat(false),
    mResult(Continue),
    mRunning(false),
    mWorld(0)
{
}

float32 Box2DRayCast::ReportFixture(b2Fixture *fixture,
                                    const b2Vec2 &point,
                                    const b2Vec2 &normal,
                                    float32 fraction)
{
    emit casted(toBox2DFixture(fixture),
                toPixels(point),
                toPixels(normal),
                fraction);

    return mResult == Clip ? fraction : static_cast<qreal>(mResult);
}

void Box2DRayCast::classBegin()
{
}

void Box2DRayCast::componentComplete()
{
    mComponentComplete = true;
    if(mRunning) {
        if(mRepeat)
            startLoop(true);
        else
            cast();
    }
}

void Box2DRayCast::cast()
{
    if(mWorld && mRunning) {
        mWorld->world().RayCast(this,mPoint1,mPoint2);
        if(!mRepeat)
            setRunning(false);
    }
}

void Box2DRayCast::startLoop(bool start)
{
    if(start)
        connect(mWorld,SIGNAL(stepped()),SLOT(cast()));
    else
    {
        mWorld->disconnect(this);
        setRunning(false);
    }
}

bool Box2DRayCast::repeat() const
{
    return mRepeat;
}

void Box2DRayCast::setRepeat(bool repeat)
{
    if(mRepeat != repeat) {
        mRepeat = repeat;
        if(mComponentComplete) {
            startLoop(mRepeat);
            emit repeatChanged();
        }
    }
}

Box2DRayCast::CastResult Box2DRayCast::result() const
{
    return mResult;
}

QPointF Box2DRayCast::point1() const
{
    return toPixels(mPoint1);
}

void Box2DRayCast::setPoint1(const QPointF &point1)
{
    if(this->point1() == point1)
        return;
    mPoint1 = toMeters(point1);
    emit point1Changed();
}

QPointF Box2DRayCast::point2() const
{
    return toPixels(mPoint2);
}

void Box2DRayCast::setPoint2(const QPointF &point2)
{
    if(this->point2() == point2)
        return;
    mPoint2 = toMeters(point2);
    emit point2Changed();
}

void Box2DRayCast::setResult(Box2DRayCast::CastResult result)
{
    mResult = result;
}

bool Box2DRayCast::running() const
{
    return mRunning;
}

void Box2DRayCast::setRunning(bool running)
{
    if(mRunning == running)
        return;
    mRunning = running;
    if(mComponentComplete) {
        if(mRepeat)
            startLoop(mRunning);
        else
            cast();
        emit runningChanged();
    }
}

Box2DWorld *Box2DRayCast::world() const
{
    return mWorld;
}

void Box2DRayCast::setWorld(Box2DWorld *world)
{
    if(mWorld != world) {
        mWorld = world;
        emit worldChanged();
    }
}
