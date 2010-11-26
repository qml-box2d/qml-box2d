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

#include "box2ddebugdraw.h"

#include "box2dworld.h"

#include <Box2D.h>

#include <QPainter>

class DebugDraw : public b2DebugDraw
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

private:
    QPainter *mP;
    b2World *mWorld;
};

DebugDraw::DebugDraw(QPainter *painter, Box2DWorld *world)
    : mP(painter)
    , mWorld(world->world())
{
    SetFlags(e_shapeBit |
             e_jointBit |
             e_aabbBit |
             e_pairBit |
             e_centerOfMassBit);
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
    mP->setPen(toQColor(color));
    mP->setBrush(Qt::NoBrush);
    mP->drawPolygon(toQPolygonF(vertices, vertexCount));
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                 const b2Color &color)
{
    mP->setPen(Qt::NoPen);
    mP->setBrush(toQColor(color));
    mP->drawPolygon(toQPolygonF(vertices, vertexCount));
}

void DebugDraw::DrawCircle(const b2Vec2 &center, float32 radius,
                           const b2Color &color)
{
    mP->setPen(toQColor(color));
    mP->setBrush(Qt::NoBrush);
    mP->drawEllipse(toQPointF(center),
                    radius * scaleRatio,
                    radius * scaleRatio);
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius,
                                const b2Vec2 &axis, const b2Color &color)
{
    Q_UNUSED(axis)

    mP->setPen(Qt::NoPen);
    mP->setBrush(toQColor(color));
    mP->drawEllipse(toQPointF(center),
                   radius * scaleRatio,
                   radius * scaleRatio);
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color)
{
    mP->setPen(toQColor(color));
    mP->drawLine(toQPointF(p1), toQPointF(p2));
}

void DebugDraw::DrawTransform(const b2Transform &xf)
{
    Q_UNUSED(xf)
    // TODO: Not sure how to draw transforms
}


Box2DDebugDraw::Box2DDebugDraw(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    mWorld(0)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
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

void Box2DDebugDraw::paint(QPainter *p, const QStyleOptionGraphicsItem *,
                           QWidget *)
{
    if (!mWorld)
        return;

    // Darken the view to make the debug draw stand out more
    p->fillRect(0, 0, width(), height(), QColor(0, 0, 0, 128));

    DebugDraw debugDraw(p, mWorld);
    debugDraw.draw();
}

void Box2DDebugDraw::onWorldStepped()
{
    if (isVisible() && opacity() > 0)
        update();
}
