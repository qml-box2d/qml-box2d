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

#include "box2ddestructionlistener.h"

#include "box2djoint.h"
#include "box2dfixture.h"

Box2DDestructionListener::Box2DDestructionListener(QObject *parent) :
    QObject(parent)
{
}

void Box2DDestructionListener::SayGoodbye(b2Joint *joint)
{
    if (joint->GetUserData()) {
        Box2DJoint *temp = toBox2DJoint(joint);
        temp->nullifyJoint();
        delete temp;
    }
}

void Box2DDestructionListener::SayGoodbye(b2Fixture *fixture)
{
    emit fixtureDestroyed(toBox2DFixture(fixture));
}
