/*
 * box2dcontactlistener.cpp
 * Copyright (c) 2014 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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

#include "box2dcontactlistener.h"

Box2DContactListener::Box2DContactListener(QObject *parent) :
    QObject(parent)
{
}

void Box2DContactListener::BeginContact(b2Contact *contact)
{
    mContact.setContact(contact);
    emit beginContact(&mContact);
}

void Box2DContactListener::EndContact(b2Contact *contact)
{
    mContact.setContact(contact);
    emit endContact(&mContact);
}

void Box2DContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    Q_UNUSED(oldManifold)
    mContact.setContact(contact);
    emit preSolve(&mContact);
}

void Box2DContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    Q_UNUSED(impulse)
    mContact.setContact(contact);
    emit postSolve(&mContact);
}
