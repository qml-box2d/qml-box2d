/*
 * box2ddebugdraw.h
 * Copyright (c) 2010 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2014 Moukhlynin Ruslan <ruslan@khvmntk.ru>
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

#include <QQuickItem>

class Box2DWorld;

class Box2DDebugDraw : public QQuickItem
{
    Q_ENUMS(DebugFlag)
    Q_OBJECT

    Q_PROPERTY(qreal axisScale READ axisScale WRITE setAxisScale NOTIFY axisScaleChanged)
    Q_PROPERTY(DebugFlag flags READ flags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(Box2DWorld *world READ world WRITE setWorld NOTIFY worldChanged)

public:
    enum DebugFlag {
        Shape = 1,
        Joint = 2,
        AABB = 4,
        Pair = 8,
        CenterOfMass = 16,
        Everything = 31
    };
    explicit Box2DDebugDraw(QQuickItem *parent = 0);

    qreal axisScale() const;
    void setAxisScale(qreal _axisScale);

    DebugFlag flags() const;
    void setFlags(DebugFlag flags);

    Box2DWorld *world() const;
    void setWorld(Box2DWorld *world);

protected:
    QSGNode *updatePaintNode(QSGNode * oldNode, UpdatePaintNodeData *);

signals:
    void axisScaleChanged();
    void flagsChanged();
    void worldChanged();

private slots:
    void onWorldStepped();

private:
    Box2DWorld *mWorld;
    qreal mAxisScale;
    DebugFlag mFlags;
};

inline qreal Box2DDebugDraw::axisScale() const
{
    return mAxisScale;
}

inline Box2DDebugDraw::DebugFlag Box2DDebugDraw::flags() const
{
    return mFlags;
}

inline Box2DWorld *Box2DDebugDraw::world() const
{
    return mWorld;
}

#endif // BOX2DDEBUGDRAW_H
