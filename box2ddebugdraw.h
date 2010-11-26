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

#ifndef BOX2DDEBUGDRAW_H
#define BOX2DDEBUGDRAW_H

#include <QDeclarativeItem>

class Box2DWorld;

class Box2DDebugDraw : public QDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(Box2DWorld *world READ world WRITE setWorld)

public:
    explicit Box2DDebugDraw(QDeclarativeItem *parent = 0);

    Box2DWorld *world() const { return mWorld; }
    void setWorld(Box2DWorld *world);

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

private slots:
    void onWorldStepped();

private:
    Box2DWorld *mWorld;
};

#endif // BOX2DDEBUGDRAW_H
