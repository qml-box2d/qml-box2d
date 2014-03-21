/*
 * box2ddebugdraw.cpp
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

#include "box2ddebugdraw.h"

#include "box2dworld.h"
#include <Box2D.h>

#include <QPainter>

class DebugDraw : public b2Draw
{
public:
    explicit DebugDraw();
    void setWorld(Box2DWorld *world);
    void draw(QPainter *painter);
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
    void setAxisLength(qreal _axisLength);
    void setDebugShow(Box2DDebugDraw::DebugShow _debugShow);

    qreal mAxisScale;
    Box2DDebugDraw::DebugShow mDebugShow;

private:
    QPainter *mPainter;
    b2World *mWorld;
};


DebugDraw::DebugDraw():
    mAxisScale(0.5),
    mDebugShow(Box2DDebugDraw::DebugShowAll),
    mWorld(0)
{
    SetFlags(Box2DDebugDraw::DebugFlagAll);
}

void DebugDraw::setWorld(Box2DWorld *world)
{
    mWorld = world->world();
    mWorld->SetDebugDraw(this);
}

void DebugDraw::draw(QPainter *painter)
{
    mPainter = painter;
    mWorld->DrawDebugData();
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
    if(mDebugShow & Box2DDebugDraw::Polygon)
    {
        mPainter->setPen(toQColor(color));
        mPainter->setBrush(Qt::NoBrush);
        mPainter->drawPolygon(toQPolygonF(vertices, vertexCount));
    }
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                 const b2Color &color)
{
    if(mDebugShow & Box2DDebugDraw::SolidPolygon)
    {
        mPainter->setPen(Qt::NoPen);
        mPainter->setBrush(toQColor(color));
        mPainter->drawPolygon(toQPolygonF(vertices, vertexCount));
    }
}

void DebugDraw::DrawCircle(const b2Vec2 &center, float32 radius,
                           const b2Color &color)
{
    if(mDebugShow & Box2DDebugDraw::Circle)
    {
        mPainter->setPen(toQColor(color));
        mPainter->setBrush(Qt::NoBrush);
        mPainter->drawEllipse(toQPointF(center),
                        radius * scaleRatio,
                        radius * scaleRatio);
    }
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius,
                                const b2Vec2 &axis, const b2Color &color)
{
    Q_UNUSED(axis)
    if(mDebugShow & Box2DDebugDraw::SolidCircle)
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
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color)
{
    if(mDebugShow & Box2DDebugDraw::Segment)
    {
        mPainter->setPen(toQColor(color));
        mPainter->drawLine(toQPointF(p1), toQPointF(p2));
    }
}

void DebugDraw::DrawTransform(const b2Transform &xf)
{
    if(mDebugShow & Box2DDebugDraw::Transform)
    {
        QPointF p1 = toQPointF(xf.p);
        QPointF p2 =  toQPointF(xf.q.GetXAxis());
        p2 = QPointF(p1.x() + mAxisScale * p2.x(),p1.y() + mAxisScale * p2.y());

        mPainter->setPen(Qt::blue); // X axis
        mPainter->drawLine(p1,p2);

        p2 =  toQPointF(xf.q.GetYAxis());
        p2 = QPointF(p1.x() + mAxisScale * p2.x(),p1.y() + mAxisScale * p2.y());

        mPainter->setPen(Qt::yellow); // Y axis
        mPainter->drawLine(p1,p2);
    }
}


Box2DDebugDraw::Box2DDebugDraw(QQuickItem *parent) :
    QQuickPaintedItem (parent),
    mWorld(0),
    mDebugDraw(new DebugDraw())
{
    setFlag(QQuickItem::ItemHasContents, true);
}

Box2DDebugDraw::~Box2DDebugDraw()
{
    if(mDebugDraw)
        delete mDebugDraw;
}

qreal Box2DDebugDraw::axisScale() const
{
    return mDebugDraw->mAxisScale;
}

void Box2DDebugDraw::setAxisScale(qreal _axisScale)
{
    if(mDebugDraw->mAxisScale != _axisScale)
    {
        mDebugDraw->mAxisScale = _axisScale;
        emit axisScaleChanged();
    }
}

Box2DDebugDraw::DebugShow Box2DDebugDraw::debugShow() const
{
    return mDebugDraw->mDebugShow;
}

void Box2DDebugDraw::setDebugShow(Box2DDebugDraw::DebugShow _debugShow)
{
    if(mDebugDraw->mDebugShow != _debugShow)
    {
        mDebugDraw->mDebugShow = _debugShow;
        emit debugShowChanged();
    }
}

Box2DDebugDraw::DebugFlag Box2DDebugDraw::debugFlag() const
{
    return static_cast<Box2DDebugDraw::DebugFlag>(mDebugDraw->GetFlags());
}

void Box2DDebugDraw::setDebugFlag(Box2DDebugDraw::DebugFlag _debugFlag)
{
    if(mDebugDraw->GetFlags() != _debugFlag)
    {
        mDebugDraw->SetFlags(_debugFlag);
        emit debugFlagChanged();
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

    // Darken the view to make the debug draw stand out more
    p->fillRect(0, 0, width(), height(), QColor(0, 0, 0, 128));
    mDebugDraw->draw(p);
}

void Box2DDebugDraw::componentComplete()
{
    QQuickItem::componentComplete();
    connect(mWorld,SIGNAL(initialized()),this,SLOT(onWorldInitialized()));
}

void Box2DDebugDraw::onWorldStepped()
{
    if (isVisible() && opacity() > 0)
        update();
}

void Box2DDebugDraw::onWorldInitialized()
{
    mDebugDraw->setWorld(mWorld);
}
