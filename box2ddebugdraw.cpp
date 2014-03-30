/*
 * box2ddebugdraw.cpp
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

#include "box2ddebugdraw.h"

#include "box2dworld.h"

#include <Box2D.h>

#include <QPainter>

class DebugDraw : public b2Draw
{
public:
    DebugDraw(QPainter *painter, Box2DWorld *world);

    void draw();

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                     const b2Color &color);
    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                          const b2Color &color);
    void DrawCircle(const b2Vec2 &center, float32 radius,
                    const b2Color &color);
    void DrawSolidCircle(const b2Vec2 &center, float32 radius,
                         const b2Vec2 &axis, const b2Color &color);
    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                     const b2Color &color);
    void DrawTransform(const b2Transform &xf);

    void setAxisScale(qreal axisScale);

private:
    QPainter *mPainter;
    b2World *mWorld;
    qreal mAxisScale;
};

DebugDraw::DebugDraw(QPainter *painter, Box2DWorld *world)
    : mPainter(painter)
    , mWorld(world->world())
{
}

void DebugDraw::draw()
{
    mWorld->SetDebugDraw(this);
    mWorld->DrawDebugData();
    mWorld->SetDebugDraw(0);
}

static QPointF toQPointF(const b2Vec2 &vec)
{
    return QPointF(vec.x * scaleRatio,
                   -vec.y * scaleRatio);
}

static QColor toQColor(const b2Color &color)
{
    return QColor(color.r * 255,
                  color.g * 255,
                  color.b * 255);
}

static QPolygonF toQPolygonF(const b2Vec2 *vertices, int32 vertexCount)
{
    QPolygonF polygon;
    polygon.reserve(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
        polygon.append(toQPointF(vertices[i]));

    return polygon;
}

void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                            const b2Color &color)
{
    mPainter->setPen(toQColor(color));
    mPainter->setBrush(Qt::NoBrush);
    mPainter->drawPolygon(toQPolygonF(vertices, vertexCount));
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                 const b2Color &color)
{
    mPainter->setPen(Qt::NoPen);
    mPainter->setBrush(toQColor(color));
    mPainter->drawPolygon(toQPolygonF(vertices, vertexCount));
}

void DebugDraw::DrawCircle(const b2Vec2 &center, float32 radius,
                           const b2Color &color)
{
    mPainter->setPen(toQColor(color));
    mPainter->setBrush(Qt::NoBrush);
    mPainter->drawEllipse(toQPointF(center),
                          radius * scaleRatio,
                          radius * scaleRatio);
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius,
                                const b2Vec2 &axis, const b2Color &color)
{
    mPainter->setPen(Qt::NoPen);
    mPainter->setBrush(toQColor(color));
    QPointF p1 = toQPointF(center);
    QPointF p2 = toQPointF(axis);
    mPainter->drawEllipse(p1,
                          radius * scaleRatio,
                          radius * scaleRatio);
    mPainter->setPen(qRgb(200,64,0));
    p2.setX(p1.x() + radius * p2.x());
    p2.setY(p1.y() + radius * p2.y());
    mPainter->drawLine(p1,p2);
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color)
{
    mPainter->setPen(toQColor(color));
    mPainter->drawLine(toQPointF(p1), toQPointF(p2));
}

void DebugDraw::DrawTransform(const b2Transform &xf)
{
    QPointF p1 = toQPointF(xf.p);
    QPointF p2 = toQPointF(xf.q.GetXAxis());
    p2 = QPointF(p1.x() + mAxisScale * p2.x(),
                 p1.y() + mAxisScale * p2.y());

    mPainter->setPen(Qt::blue); // X axis
    mPainter->drawLine(p1,p2);

    p2 = toQPointF(xf.q.GetYAxis());
    p2 = QPointF(p1.x() + mAxisScale * p2.x(),
                 p1.y() + mAxisScale * p2.y());

    mPainter->setPen(Qt::yellow); // Y axis
    mPainter->drawLine(p1,p2);
}

void DebugDraw::setAxisScale(qreal axisScale)
{
    mAxisScale = axisScale;
}


Box2DDebugDraw::Box2DDebugDraw(QQuickItem *parent) :
    QQuickPaintedItem (parent),
    mWorld(0),
    mAxisScale(0.5),
    mFlags(Everything)

{
    setFlag(QQuickItem::ItemHasContents, true);
}

qreal Box2DDebugDraw::axisScale() const
{
    return mAxisScale;
}

void Box2DDebugDraw::setAxisScale(qreal _axisScale)
{
    if (mAxisScale != _axisScale) {
        mAxisScale = _axisScale;
        emit axisScaleChanged();
    }
}

Box2DDebugDraw::DebugFlag Box2DDebugDraw::flags() const
{
    return mFlags;
}

void Box2DDebugDraw::setFlags(DebugFlag flags)
{
    if (mFlags != flags) {
        mFlags = flags;
        emit flagsChanged();
    }
}

void Box2DDebugDraw::setWorld(Box2DWorld *world)
{
    if (mWorld == world)
        return;

    if (mWorld)
        mWorld->disconnect(this);

    mWorld = world;

    if (mWorld)
        connect(mWorld, SIGNAL(stepped()), SLOT(onWorldStepped()));
}

void Box2DDebugDraw::paint(QPainter *p)
{
    if (!mWorld)
        return;

    DebugDraw debugDraw(p, mWorld);
    debugDraw.SetFlags(mFlags);
    debugDraw.setAxisScale(mAxisScale);
    debugDraw.draw();
}

void Box2DDebugDraw::onWorldStepped()
{
    if (isVisible() && opacity() > 0)
        update();
}
