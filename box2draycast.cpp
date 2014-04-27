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

#include "box2dbody.h"
#include "box2dfixture.h"
#include "box2dworld.h"

Box2DRayCast::Box2DRayCast(QObject *parent) :
    QObject(parent),
    mMaxFraction(-1.0f)
{
}

float32 Box2DRayCast::ReportFixture(b2Fixture *fixture,
                                    const b2Vec2 &point,
                                    const b2Vec2 &normal,
                                    float32 fraction)
{
    mMaxFraction = -1.0f;

    Box2DFixture *box2dFixture = toBox2DFixture(fixture);
    Box2DWorld *world = box2dFixture->getBody()->world();

    emit fixtureReported(box2dFixture,
                         world->toPixels(point),
                         world->toPixels(normal),
                         fraction);

    return mMaxFraction;
}
