/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the Box2D QML plugin.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BOX2DBODY_H
#define BOX2DBODY_H

#include <QDeclarativeItem>

class Box2DWorld;

class b2Body;
class b2World;

/**
 * The Box2D body, build up from a list of shapes.
 */
class Box2DBody : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(bool fixed READ fixed WRITE setFixed)

public:
    explicit Box2DBody(QDeclarativeItem *parent = 0);
    ~Box2DBody();

    bool fixed() const
    { return mFixed; }

    void setFixed(bool fixed)
    { mFixed = fixed; }

    void componentComplete();

    void initialize(b2World *world);
    void synchronize();
    void cleanup(b2World *world);

private:
    b2Body *mBody;
    bool mFixed;
};

#endif // BOX2DBODY_H
