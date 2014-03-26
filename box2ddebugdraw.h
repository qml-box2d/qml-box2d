/*
 * box2ddebugdraw.h
 * Copyright (c) 2010 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2014 Ruslan Moukhlynin <ruslan@khvmntk.ru>
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
class DebugDraw;

class Box2DDebugDraw : public QQuickPaintedItem
{
    Q_OBJECT

    Q_ENUMS(DebugShape)
    Q_ENUMS(DebugFlag)
    Q_PROPERTY(qreal axisScale READ axisScale WRITE setAxisScale NOTIFY axisScaleChanged)
    Q_PROPERTY(DebugShape debugShape READ debugShape WRITE setDebugShape NOTIFY debugShapeChanged)
    Q_PROPERTY(DebugFlag debugFlag READ debugFlag WRITE setDebugFlag NOTIFY debugFlagChanged)
    Q_PROPERTY(Box2DWorld *world READ world WRITE setWorld)

public:
    enum DebugShape {
        Polygon = 1,
        SolidPolygon = 2,
        Circle = 4,
        SolidCircle = 8,
        Segment = 16,
        Transform = 32,
        DebugShowAll = 63
    };
    enum DebugFlag {
        ShapeBit = 1,
        JointBit = 2,
        AABBBit = 4,
        PairBit = 8,
        CenterOfMassBit = 16,
        DebugFlagAll = 31
    };
    explicit Box2DDebugDraw(QQuickItem *parent = 0);
    ~Box2DDebugDraw();

    qreal axisScale() const;
    void setAxisScale(qreal _axisScale);

    DebugFlag debugFlag() const;
    void setDebugFlag(DebugFlag _debugFlag);

    DebugShape debugShape() const;
    void setDebugShape(DebugShape _debugShow);

    Box2DWorld *world() const { return mWorld; }
    void setWorld(Box2DWorld *world);

    void paint(QPainter *);

protected:
    void componentComplete();

private slots:
    void onWorldStepped();
    void onWorldInitialized();

private:
    Box2DWorld *mWorld;
    DebugDraw * mDebugDraw;

signals:
    void axisScaleChanged();
    void debugShapeChanged();
    void debugFlagChanged();
};

#endif // BOX2DDEBUGDRAW_H
