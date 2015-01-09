/*
 * box2dcontactlistener.h
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

#ifndef BOX2DCONTACTLISTENER_H
#define BOX2DCONTACTLISTENER_H

#include <QObject>

#include "box2dcontact.h"

class Box2DContactListener : public QObject, public b2ContactListener
{
    Q_OBJECT

public:
    explicit Box2DContactListener(QObject *parent = 0);

    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);

signals:
    void beginContact(Box2DContact *contact);
    void endContact(Box2DContact *contact);
    void preSolve(Box2DContact *contact);
    void postSolve(Box2DContact *contact);

private:
    Box2DContact mContact;
};

#endif // BOX2DCONTACTLISTENER_H
