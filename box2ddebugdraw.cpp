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


Box2DDebugDraw::Box2DDebugDraw(QQuickItem *parent) :
    QQuickPaintedItem (parent),
    mWorld(0)
{
    setFlag(QQuickItem::ItemHasContents, true);
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

    // Darken the view to make the debug draw stand out more
    p->fillRect(0, 0, width(), height(), QColor(0, 0, 0, 128));

    DebugDraw debugDraw(p, mWorld);
    debugDraw.draw();
}

void Box2DDebugDraw::onWorldStepped()
{
    if (isVisible() && opacity() > 0)
    {
        update();
    }
}
