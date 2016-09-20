/*
 * box2dfixture.cpp
 * Copyright (c) 2010-2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2011 Daker Fernandes Pinheiro <daker.pinheiro@openbossa.org>
 * Copyright (c) 2011 Alessandro Portale <alessandro.portale@nokia.com>
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

#include "box2dfixture.h"

#include "box2dbody.h"
#include "box2dworld.h"

#include <QDebug>

#include "Common/b2Math.h"

Box2DFixture::Box2DFixture(QObject *parent) :
    QObject(parent),
    mFixture(0),
    mBody(0)
{
    mFixtureDef.userData = this;
}

float Box2DFixture::density() const
{
    return mFixtureDef.density;
}

void Box2DFixture::setDensity(float density)
{
    if (mFixtureDef.density == density)
        return;

    mFixtureDef.density = density;
    if (mFixture)
        mFixture->SetDensity(density);
    emit densityChanged();
}

float Box2DFixture::friction() const
{
    return mFixtureDef.friction;
}

void Box2DFixture::setFriction(float friction)
{
    if (mFixtureDef.friction == friction)
        return;

    mFixtureDef.friction = friction;
    if (mFixture)
        mFixture->SetFriction(friction);
    emit frictionChanged();
}

float Box2DFixture::restitution() const
{
    return mFixtureDef.restitution;
}

void Box2DFixture::setRestitution(float restitution)
{
    if (mFixtureDef.restitution == restitution)
        return;

    mFixtureDef.restitution = restitution;
    if (mFixture)
        mFixture->SetRestitution(restitution);
    emit restitutionChanged();
}

bool Box2DFixture::isSensor() const
{
    return mFixtureDef.isSensor;
}

void Box2DFixture::setSensor(bool sensor)
{
    if (mFixtureDef.isSensor == sensor)
        return;

    mFixtureDef.isSensor = sensor;
    if (mFixture)
        mFixture->SetSensor(sensor);
    emit sensorChanged();
}

Box2DFixture::CategoryFlags Box2DFixture::categories() const
{
    return CategoryFlags(mFixtureDef.filter.categoryBits);
}

void Box2DFixture::setCategories(CategoryFlags layers)
{
    if (mFixtureDef.filter.categoryBits == layers)
        return;

    mFixtureDef.filter.categoryBits = layers;
    if (mFixture)
        mFixture->SetFilterData(mFixtureDef.filter);

    emit categoriesChanged();
}

Box2DFixture::CategoryFlags Box2DFixture::collidesWith() const
{
    return CategoryFlags(mFixtureDef.filter.maskBits);
}

void Box2DFixture::setCollidesWith(CategoryFlags layers)
{
    if (mFixtureDef.filter.maskBits == layers)
        return;

    mFixtureDef.filter.maskBits = layers;
    if (mFixture)
        mFixture->SetFilterData(mFixtureDef.filter);

    emit collidesWithChanged();
}

int Box2DFixture::groupIndex() const
{
    return mFixtureDef.filter.groupIndex;
}

void Box2DFixture::setGroupIndex(int groupIndex)
{
    if (mFixtureDef.filter.groupIndex == groupIndex)
        return;

    mFixtureDef.filter.groupIndex = groupIndex;
    if (mFixture)
        mFixture->SetFilterData(mFixtureDef.filter);

    emit groupIndexChanged();
}

void Box2DFixture::initialize(Box2DBody *body)
{
    mBody = body;
    b2Shape *shape = createShape();
    if (!shape)
        return;

    mFixtureDef.shape = shape;
    mFixture = body->body()->CreateFixture(&mFixtureDef);
    delete shape;
}

void Box2DFixture::recreateFixture()
{
    if (!mBody)
        return;
    if (mFixture)
        mBody->body()->DestroyFixture(mFixture);
    initialize(mBody);
}

Box2DBody *Box2DFixture::getBody() const
{
    return mBody;
}

//=================== BOX =======================

void Box2DBox::setX(qreal x)
{
    if (mPosition.x() == x)
        return;
    mPosition.setX(x);
    recreateFixture();
    emit xChanged();
}

void Box2DBox::setY(qreal y)
{
    if (mPosition.y() == y)
        return;
    mPosition.setY(y);
    recreateFixture();
    emit yChanged();
}

void Box2DBox::setWidth(qreal width)
{
    if (mSize.width() == width)
        return;
    mSize.setWidth(width);
    recreateFixture();
    emit widthChanged();
}

void Box2DBox::setHeight(qreal height)
{
    if (mSize.height() == height)
        return;
    mSize.setHeight(height);
    recreateFixture();
    emit heightChanged();
}

void Box2DBox::setRotation(qreal rotation)
{
    if (mRotation == rotation)
        return;
    mRotation = rotation;
    recreateFixture();
    emit rotationChanged();
}

b2Shape *Box2DBox::createShape()
{
    const qreal halfWidth = width() * 0.5;
    const qreal halfHeight = height() * 0.5;
    const QPointF center(x() + halfWidth,
                         y() + halfHeight);

    b2PolygonShape *shape = new b2PolygonShape;
    shape->SetAsBox(b2Max(mBody->world()->toMeters(halfWidth), b2_linearSlop),
                    b2Max(mBody->world()->toMeters(halfHeight), b2_linearSlop),
                    mBody->world()->toMeters(center),
                    toRadians(rotation()));

    return shape;
}

//=================== CIRCLE =======================

void Box2DCircle::setX(qreal x)
{
    if (mPosition.x() == x)
        return;
    mPosition.setX(x);
    recreateFixture();
    emit xChanged();
}

void Box2DCircle::setY(qreal y)
{
    if (mPosition.y() == y)
        return;
    mPosition.setY(y);
    recreateFixture();
    emit yChanged();
}

void Box2DCircle::setRadius(float radius)
{
    if (mRadius == radius)
        return;
    mRadius = radius;
    recreateFixture();
    emit radiusChanged();
}

b2Shape *Box2DCircle::createShape()
{
    b2CircleShape *shape = new b2CircleShape;

    shape->m_radius = mBody->world()->toMeters(radius());
    shape->m_p = mBody->world()->toMeters(position() + QPointF(radius(), radius()));

    return shape;
}

//=================== POLYGON =======================

void Box2DPolygon::setVertices(const QVariantList &vertices)
{
    if (vertices == mVertices)
        return;

    mVertices = vertices;
    recreateFixture();
    emit verticesChanged();
}

b2Shape *Box2DPolygon::createShape()
{
    const int count = mVertices.length();
    if (count < 2 || count > b2_maxPolygonVertices) {
        qWarning() << "Polygon: Invalid number of vertices:" << count;
        return 0;
    }

    QScopedArrayPointer<b2Vec2> vertices(new b2Vec2[count]);

    for (int i = 0; i < count; ++i) {
        vertices[i] = mBody->world()->toMeters(mVertices.at(i).toPointF());

        if (i > 0) {
            if (b2DistanceSquared(vertices[i - 1], vertices[i]) <= b2_linearSlop * b2_linearSlop) {
                qWarning() << "Polygon: vertices are too close together";
                return 0;
            }
        }
    }

    b2PolygonShape *shape = new b2PolygonShape;
    shape->Set(vertices.data(), count);

    return shape;
}

//=================== CHAIN =======================

Box2DChain::Box2DChain(QQuickItem *parent) :
    Box2DFixture(parent),
    mLoop(false),
    mPrevVertexFlag(false),
    mNextVertexFlag(false)
{
}

void Box2DChain::setVertices(const QVariantList &vertices)
{
    if (vertices == mVertices)
        return;

    mVertices = vertices;
    recreateFixture();
    emit verticesChanged();
}

void Box2DChain::setLoop(bool loop)
{
    if (mLoop == loop)
        return;

    mLoop = loop;
    recreateFixture();
    emit loopChanged();
}

void Box2DChain::setPrevVertex(const QPointF &prevVertex)
{
    if (mPrevVertexFlag && mPrevVertex == prevVertex)
        return;

    mPrevVertex = prevVertex;
    mPrevVertexFlag = true;
    recreateFixture();
    emit prevVertexChanged();
}

void Box2DChain::setNextVertex(const QPointF &nextVertex)
{
    if (mNextVertexFlag && mNextVertex == nextVertex)
        return;

    mNextVertex = nextVertex;
    mNextVertexFlag = true;
    recreateFixture();
    emit nextVertexChanged();
}

b2Shape *Box2DChain::createShape()
{
    const int count = mVertices.length();

    if (count < 2 || (mLoop && count < 3)) {
        qWarning() << "Chain: Invalid number of vertices:" << count;
        return 0;
    }

    QScopedArrayPointer<b2Vec2> vertices(new b2Vec2[count]);

    for (int i = 0; i < count; ++i) {
        vertices[i] = mBody->world()->toMeters(mVertices.at(i).toPointF());

        if (i > 0) {
            if (b2DistanceSquared(vertices[i - 1], vertices[i]) <= b2_linearSlop * b2_linearSlop) {
                qWarning() << "Chain: vertices are too close together";
                return 0;
            }
        }
    }

    b2ChainShape *shape = new b2ChainShape;
    if (mLoop) {
        shape->CreateLoop(vertices.data(), count);
    } else {
        shape->CreateChain(vertices.data(), count);

        if (mPrevVertexFlag)
            shape->SetPrevVertex(mBody->world()->toMeters(mPrevVertex));
        if (mNextVertexFlag)
            shape->SetNextVertex(mBody->world()->toMeters(mNextVertex));
    }

    return shape;
}

//=================== EDGE =======================

void Box2DEdge::setVertices(const QVariantList &vertices)
{
    if (vertices == mVertices)
        return;

    mVertices = vertices;
    recreateFixture();
    emit verticesChanged();
}

b2Shape *Box2DEdge::createShape()
{
    const int count = mVertices.length();
    if (count != 2) {
        qWarning() << "Edge: Invalid number of vertices:" << count;
        return 0;
    }
    const b2Vec2 vertex1 = mBody->world()->toMeters(mVertices.at(0).toPointF());
    const b2Vec2 vertex2 = mBody->world()->toMeters(mVertices.at(1).toPointF());
    if (b2DistanceSquared(vertex1, vertex2) <= b2_linearSlop * b2_linearSlop) {
        qWarning() << "Edge: vertices are too close together";
        return 0;
    }
    b2EdgeShape *shape = new b2EdgeShape;
    shape->Set(vertex1, vertex2);

    return shape;
}
