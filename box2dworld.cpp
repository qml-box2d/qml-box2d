/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the QmlArcade.
 *
 * QmlArcade is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * QmlArcade is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QmlArcade.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2dworld.h"

#include <Box2D.h>

Box2DWorld::Box2DWorld(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // Define the world boundaries and its gravity
    b2AABB bounds;
    bounds.lowerBound.Set(-100.0f, -100.0f);
    bounds.upperBound.Set(100.0f, 100.0f);

    b2Vec2 gravity(0.0f, -10.0f);
    bool doSleep = true;

    mWorld = new b2World(bounds, gravity, doSleep);
}

Box2DWorld::~Box2DWorld()
{
    delete mWorld;
}
