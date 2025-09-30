/*
 * box2ddebugdraw.cpp
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

#define CIRCLE_SEGMENTS_COUNT 32
#define LINE_WIDTH 1

#include "box2ddebugdraw.h"

#include "box2dworld.h"

#include <box2d/box2d.h>

#include <QPainter>
#include <QSGNode>
#include <QSGFlatColorMaterial>
#include <QtCore/qmath.h>

class DebugDraw : public b2Draw
{
public:
    DebugDraw(QSGNode *root, Box2DWorld &world);

    void draw();

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                     const b2Color &color) override;
    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                          const b2Color &color) override;
    void DrawCircle(const b2Vec2 &center, float radius,
                    const b2Color &color) override;
    void DrawSolidCircle(const b2Vec2 &center, float radius,
                         const b2Vec2 &axis, const b2Color &color) override;
    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                     const b2Color &color) override;
    void DrawTransform(const b2Transform &xf) override;
    void DrawPoint(const b2Vec2 &p, float size,
                     const b2Color &color) override;

    void setAxisScale(qreal axisScale);

private:
    QSGNode *mRoot;
    Box2DWorld &mWorld;
    qreal mAxisScale;

    QSGNode *createNode(QSGGeometry *geometry, const QColor &color, QSGNode *parent = nullptr);
};

DebugDraw::DebugDraw(QSGNode *root, Box2DWorld &world) :
    mRoot(root),
    mWorld(world)
{
}

void DebugDraw::draw()
{
    mWorld.world().SetDebugDraw(this);
    mWorld.world().DebugDraw();
    mWorld.world().SetDebugDraw(nullptr);
}

static QColor toQColor(const b2Color &color)
{
    return QColor(color.r * 255,
                  color.g * 255,
                  color.b * 255,
                  color.a * 255);
}

QSGNode *DebugDraw::createNode(QSGGeometry *geometry, const QColor &color, QSGNode *parent)
{
    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(color);

    QSGGeometryNode *node = new QSGGeometryNode;
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);
    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    if (parent)
        parent->appendChildNode(node);
    else
        mRoot->appendChildNode(node);
    return node;
}

void DebugDraw::DrawPolygon(const b2Vec2 *vertices,
                            int32 vertexCount,
                            const b2Color &color)
{
    Q_ASSERT(vertexCount > 1);

    // We'd use QSGGeometry::DrawLineLoop, but it's not supported in Qt 6
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
                                            vertexCount + 1);
    geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
    geometry->setLineWidth(LINE_WIDTH);

    QSGGeometry::Point2D *points = geometry->vertexDataAsPoint2D();
    for (int i = 0; i < vertexCount; ++i) {
        QPointF point = mWorld.toPixels(vertices[i]);
        points[i].set(point.x(), point.y());
    }
    points[vertexCount] = points[0];

    createNode(geometry, toQColor(color));
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices,
                                 int32 vertexCount,
                                 const b2Color &color)
{
    Q_ASSERT(vertexCount > 2);

    // We'd use QSGGeometry::DrawTriangleFan, but it's not supported in Qt 6
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
                                            (vertexCount - 2) * 3);
    geometry->setDrawingMode(QSGGeometry::DrawTriangles);
    geometry->setLineWidth(LINE_WIDTH);

    const QPointF origin = mWorld.toPixels(vertices[0]);

    QSGGeometry::Point2D *points = geometry->vertexDataAsPoint2D();
    QPointF prev = mWorld.toPixels(vertices[1]);
    for (int i = 2; i < vertexCount; ++i) {
        const QPointF cur = mWorld.toPixels(vertices[i]);

        const int triangleStart = (i - 2) * 3;
        points[triangleStart].set(origin.x(), origin.y());
        points[triangleStart + 1].set(prev.x(), prev.y());
        points[triangleStart + 2].set(cur.x(), cur.y());
        prev = cur;
    }

    createNode(geometry, toQColor(color));
}

void DebugDraw::DrawCircle(const b2Vec2 &center,
                           float radius,
                           const b2Color &color)
{
    // We'd use QSGGeometry::DrawLineLoop, but it's not supported in Qt 6
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
                                            CIRCLE_SEGMENTS_COUNT + 1);
    geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
    geometry->setLineWidth(LINE_WIDTH);

    QPointF centerInPixels = mWorld.toPixels(center);
    qreal radiusInPixels = mWorld.toPixels(radius);

    QSGGeometry::Point2D *points = geometry->vertexDataAsPoint2D();
    for (int i = 0; i <= CIRCLE_SEGMENTS_COUNT; ++i) {
        const float theta = i * 2 * M_PI / CIRCLE_SEGMENTS_COUNT;
        points[i].set(centerInPixels.x() + radiusInPixels * qCos(theta),
                      centerInPixels.y() + radiusInPixels * qSin(theta));
    }

    createNode(geometry, toQColor(color));
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float radius,
                                const b2Vec2 &axis, const b2Color &color)
{
    // We'd use QSGGeometry::DrawTriangleFan, but it's not supported in Qt 6
    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
                                            CIRCLE_SEGMENTS_COUNT * 3);
    geometry->setDrawingMode(QSGGeometry::DrawTriangles);
    geometry->setLineWidth(LINE_WIDTH);

    QPointF centerInPixels = mWorld.toPixels(center);
    QPointF axisInPixels = mWorld.toPixels(axis);
    qreal radiusInPixels = mWorld.toPixels(radius);
    axisInPixels.setX(centerInPixels.x() + radius * axisInPixels.x());
    axisInPixels.setY(centerInPixels.y() + radius * axisInPixels.y());

    QSGGeometry::Point2D *points = geometry->vertexDataAsPoint2D();
    QSGGeometry::Point2D lastPoint;
    lastPoint.set(centerInPixels.x() + radiusInPixels,
                  centerInPixels.y());

    for (int i = 1; i <= CIRCLE_SEGMENTS_COUNT; ++i) {
        const float theta = i * 2 * M_PI / CIRCLE_SEGMENTS_COUNT;
        QSGGeometry::Point2D currentPoint;
        currentPoint.set(centerInPixels.x() + radiusInPixels * qCos(theta),
                         centerInPixels.y() + radiusInPixels * qSin(theta));

        const int triangleStart = (i - 1) * 3;
        points[triangleStart].set(centerInPixels.x(), centerInPixels.y());
        points[triangleStart + 1] = lastPoint;
        points[triangleStart + 2] = currentPoint;
        lastPoint = currentPoint;
    }
    QSGNode *node = createNode(geometry, toQColor(color));

    QSGGeometry *axisGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    axisGeometry->setDrawingMode(QSGGeometry::DrawLines);
    axisGeometry->setLineWidth(LINE_WIDTH);

    axisGeometry->vertexDataAsPoint2D()[0].set(centerInPixels.x(), centerInPixels.y());
    axisGeometry->vertexDataAsPoint2D()[1].set(axisInPixels.x(), axisInPixels.y());
    createNode(axisGeometry, qRgb(200, 64, 0), node);
}

void DebugDraw::DrawSegment(const b2Vec2 &p1,
                            const b2Vec2 &p2,
                            const b2Color &color)
{
    QPointF p1InPixels = mWorld.toPixels(p1);
    QPointF p2InPixels = mWorld.toPixels(p2);

    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometry->setDrawingMode(QSGGeometry::DrawLines);
    geometry->setLineWidth(LINE_WIDTH);

    geometry->vertexDataAsPoint2D()[0].set(p1InPixels.x(), p1InPixels.y());
    geometry->vertexDataAsPoint2D()[1].set(p2InPixels.x(), p2InPixels.y());

    createNode(geometry, toQColor(color));
}

void DebugDraw::DrawTransform(const b2Transform &xf)
{
    QPointF p1 = mWorld.toPixels(xf.p);
    QPointF p2 = mWorld.toPixels(xf.q.GetXAxis());
    p2 = QPointF(p1.x() + mAxisScale * p2.x(),
                 p1.y() + mAxisScale * p2.y());

    QSGGeometry *geometryX = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometryX->setDrawingMode(QSGGeometry::DrawLines);
    geometryX->setLineWidth(LINE_WIDTH);
    geometryX->vertexDataAsPoint2D()[0].set(p1.x(), p1.y());
    geometryX->vertexDataAsPoint2D()[1].set(p2.x(), p2.y());
    createNode(geometryX,Qt::blue);

    p2 = mWorld.toPixels(xf.q.GetYAxis());
    p2 = QPointF(p1.x() + mAxisScale * p2.x(),
                 p1.y() + mAxisScale * p2.y());

    QSGGeometry *geometryY = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometryY->setDrawingMode(QSGGeometry::DrawLines);
    geometryY->setLineWidth(LINE_WIDTH);
    geometryY->vertexDataAsPoint2D()[0].set(p1.x(), p1.y());
    geometryY->vertexDataAsPoint2D()[1].set(p2.x(), p2.y());

    createNode(geometryY, Qt::yellow);
}

void DebugDraw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color)
{
    // TODO Check
    QPointF pInPixels = mWorld.toPixels(p);

    QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometry->setDrawingMode(QSGGeometry::DrawPoints);
    geometry->setLineWidth(size);

    geometry->vertexDataAsPoint2D()[0].set(pInPixels.x(), pInPixels.y());

    createNode(geometry, toQColor(color));

}

void DebugDraw::setAxisScale(qreal axisScale)
{
    mAxisScale = axisScale;
}

Box2DDebugDraw::Box2DDebugDraw(QQuickItem *parent) :
    QQuickItem(parent),
    mWorld(nullptr),
    mAxisScale(0.5),
    mFlags(Everything)
{
    setFlag(QQuickItem::ItemHasContents, true);
    setWorld(Box2DWorld::defaultWorld());
}

void Box2DDebugDraw::setAxisScale(qreal axisScale)
{
    if (mAxisScale != axisScale) {
        mAxisScale = axisScale;
        emit axisScaleChanged();
    }
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

    emit worldChanged();
}

QSGNode *Box2DDebugDraw::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    if (oldNode)
        delete oldNode;

    if (!mWorld)
        return nullptr;

    QSGTransformNode *root = new QSGTransformNode;
    DebugDraw debugDraw(root, *mWorld);
    debugDraw.SetFlags(mFlags);
    debugDraw.setAxisScale(mAxisScale);
    debugDraw.draw();
    return root;
}

void Box2DDebugDraw::onWorldStepped()
{
    if (isVisible() && opacity() > 0)
        update();
}

#include "moc_box2ddebugdraw.cpp"
