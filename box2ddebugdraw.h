/*
 * box2ddebugdraw.h
 * Copyright (c) 2010 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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

#ifndef BOX2DDEBUGDRAW_H
#define BOX2DDEBUGDRAW_H

#include <QQuickPaintedItem>
#include <QQuickItem>

class Box2DWorld;

class Box2DDebugDraw : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(Box2DWorld *world READ world WRITE setWorld)

public:
    explicit Box2DDebugDraw(QQuickItem *parent = 0);

    Box2DWorld *world() const { return mWorld; }
    void setWorld(Box2DWorld *world);

    void paint(QPainter *);

private slots:
    void onWorldStepped();

private:
    Box2DWorld *mWorld;
};

#endif // BOX2DDEBUGDRAW_H
