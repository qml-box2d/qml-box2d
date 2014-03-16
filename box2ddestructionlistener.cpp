/*
 * box2ddestructionlistener.cpp
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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

#include "box2ddestructionlistener.h"

#include "box2djoint.h"
#include "box2dfixture.h"

Box2DDestructionListener::Box2DDestructionListener(QObject *parent) :
    QObject(parent)
{
}

void Box2DDestructionListener::SayGoodbye(b2Joint *joint)
{
    if (Box2DJoint *temp = toBox2DJoint(joint)) {
        temp->nullifyJoint();
        delete temp;
    }
}

void Box2DDestructionListener::SayGoodbye(b2Fixture *fixture)
{
    emit fixtureDestroyed(toBox2DFixture(fixture));
}
