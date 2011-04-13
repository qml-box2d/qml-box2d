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

#ifndef BOX2DDESTRUCTIONLISTENER_H
#define BOX2DDESTRUCTIONLISTENER_H

#include <QObject>
#include <Box2D.h>

class Box2DFixture;

class Box2DDestructionListener : public QObject, public b2DestructionListener
{
    Q_OBJECT

public:
    explicit Box2DDestructionListener(QObject *parent = 0);

    void SayGoodbye(b2Joint *joint);

    void SayGoodbye(b2Fixture *fixture);

signals:
    void fixtureDestroyed(Box2DFixture *fixture);
};

#endif // BOX2DDESTRUCTIONLISTENER_H
