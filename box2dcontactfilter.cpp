/*
 * box2dcontactfilter.cpp
 * Copyright (c) 2014 Ruslan Mouchlynin <ruslan@khvmntk.ru>
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

#include "box2dcontactfilter.h"

#include "box2dworld.h"
#include "box2dfixture.h"

Box2DContactFilter::Box2DContactFilter(QObject *parent) :
    QObject(parent),
    mEnabled(true),
    mWorld(0)
{
}

bool Box2DContactFilter::ShouldCollide(b2Fixture *fixtureA, b2Fixture *fixtureB)
{
    mResult = true;
    emit contacted(toBox2DFixture(fixtureA),
                   toBox2DFixture(fixtureB));

    return mResult;
}

void Box2DContactFilter::classBegin()
{
}

void Box2DContactFilter::componentComplete()
{
    installContactFilter(mEnabled);
}

bool Box2DContactFilter::isEnabled() const
{
    return mEnabled;
}

void Box2DContactFilter::setEnabled(bool enabled)
{
    if(mEnabled == enabled)
        return;
    mEnabled = enabled;
    installContactFilter(mEnabled);
    emit enabledChanged();
}

bool Box2DContactFilter::result() const
{
    return mResult;
}

void Box2DContactFilter::setResult(bool result)
{
    mResult = result;
}

Box2DWorld *Box2DContactFilter::world() const
{
    return mWorld;
}

void Box2DContactFilter::setWorld(Box2DWorld *world)
{
    if(mWorld == world)
        return;
    mWorld = world;
    emit worldChanged();
}

void Box2DContactFilter::installContactFilter(bool install)
{
    if(mWorld) {
        if(install)
            mWorld->world().SetContactFilter(this);
        else
            mWorld->world().SetContactFilter(0);
    }
}
