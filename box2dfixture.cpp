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
#include "box2dworld.h"
#include <QDebug>
#include "Common/b2Math.h"

Box2DFixture::Box2DFixture(QQuickItem *parent) :
    QQuickItem(parent),
    mFixture(0),
    mFixtureDef(),
    factorWidth(1.0),
    factorHeight(1.0)
{
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
    emit groupIndexChanged();
}

void Box2DFixture::createFixture(b2Body *body)
{
    b2Shape *shape = createShape();
    if (!shape)
        return;

    mFixtureDef.shape = shape;
    mFixture = body->CreateFixture(&mFixtureDef);
    mFixture->SetUserData(this);
    mBody = body;
    delete shape;
}

Box2DBody *Box2DFixture::GetBody() const
{
    return static_cast<Box2DBody *>(mBody->GetUserData());
}

void Box2DFixture::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if(!isComponentComplete()) return;

    qreal nw = newGeometry.width();
    qreal nh = newGeometry.height();
    qreal ow = oldGeometry.width();
    qreal oh = oldGeometry.height();

    if( (nw != ow && !qFuzzyCompare(ow,0.0)) ||  (nh != oh && !qFuzzyCompare(oh,0.0)) )
    {
        factorWidth = nw / ow;
        factorHeight = nh / oh;
        scale();
    }
}

void Box2DFixture::emitBeginContact(Box2DFixture *other)
{
    emit beginContact(other);
}

void Box2DFixture::emitContactChanged(Box2DFixture *other)
{
    emit contactChanged(other);
}

void Box2DFixture::emitEndContact(Box2DFixture *other)
{
    emit endContact(other);
}

void Box2DFixture::applyShape(b2Shape *shape)
{
    if(mFixture) mBody->DestroyFixture(mFixture);
    mFixtureDef.shape = shape;
    mFixture = mBody->CreateFixture(&mFixtureDef);
    mFixture->SetUserData(this);
    delete shape;
}

b2Vec2 *Box2DVerticesShape::scaleVertices()
{
    const int count = mVertices.length();
    b2Vec2 * vertices = new b2Vec2[count];
    for (int i = 0; i < count; ++i) {

        QPointF point = mVertices.at(i).toPointF();
        point.setX(point.x() * factorWidth);
        point.setY(point.y() * factorHeight);
        mVertices.replace(i,point);
        vertices[i].Set(point.x() / scaleRatio, -point.y() / scaleRatio);
    }
    return vertices;
}

//=================== BOX =======================

b2Shape *Box2DBox::createShape()
{
    const qreal _x = x() / scaleRatio;
    const qreal _y = -y() / scaleRatio;
    const qreal _width = width() / scaleRatio;
    const qreal _height = height() / scaleRatio;

    vertices[0].Set(_x, _y);
    vertices[1].Set(_x , _y - _height);
    vertices[2].Set(_x + _width , _y - _height);
    vertices[3].Set(_x + _width , _y );
    for(int i = 1;i < 4;i ++)
    {
        if(i > 0)
        {
            if(b2DistanceSquared(vertices[i - 1], vertices[i]) <= b2_linearSlop * b2_linearSlop)
            {
                qWarning() << "Box: vertices are too close together";
                return 0;
            }
        }
    }

    int32 count = 4;
    b2PolygonShape *shape = new b2PolygonShape;
    shape->Set(vertices, count);
    return shape;
}

void Box2DBox::scale()
{
    if(mFixture)
    {
        b2Shape * shape = createShape();
        applyShape(shape);
    }
}

//=================== CIRCLE =======================

b2Shape *Box2DCircle::createShape()
{
    b2CircleShape *shape = new b2CircleShape;
    shape->m_radius = mRadius / scaleRatio;
    shape->m_p.Set(shape->m_radius, -shape->m_radius);
    if(height() == 0 || width() == 0) {
        this->setWidth(shape->m_radius);
        this->setHeight(shape->m_radius);
    }
    return shape;
}

void Box2DCircle::scale()
{
    if(mFixture)
    {
        b2Shape * shape = createShape();
        applyShape(shape);
    }
}

//=================== POLYGON =======================

b2Shape *Box2DPolygon::createShape()
{
    const int count = mVertices.length();
    if (count < 2 || count > b2_maxPolygonVertices) {
        qWarning() << "Polygon: Invalid number of vertices:" << count;
        return 0;
    }

    b2Vec2 *vertices = new b2Vec2[count];
    for (int i = 0; i < count; ++i) {
        const QPointF &point = mVertices.at(i).toPointF();
        vertices[i].Set(point.x() / scaleRatio, -point.y() / scaleRatio);
        if(i > 0)
        {
            if(b2DistanceSquared(vertices[i - 1], vertices[i]) <= b2_linearSlop * b2_linearSlop)
            {
                qWarning() << "Polygon: vertices are too close together";
                return 0;
            }
        }
    }

    b2PolygonShape *shape = new b2PolygonShape;
    shape->Set(vertices, count);
    delete[] vertices;
    return shape;
}

void Box2DPolygon::scale()
{
    if(mFixture)
    {
        b2Vec2 *vertices = scaleVertices();
        b2PolygonShape *shape = new b2PolygonShape;
        shape->Set(vertices, mVertices.count());
        delete[] vertices;
        applyShape(shape);
    }

}

//=================== CHAIN =======================

b2Shape *Box2DChain::createShape()
{
    const int count = mVertices.length();
    if (count < 2) {
        qWarning() << "Chain: Invalid number of vertices:" << count;
        return 0;
    }

    b2Vec2 *vertices = new b2Vec2[count];
    for (int i = 0; i < count; ++i) {
        const QPointF &point = mVertices.at(i).toPointF();
        vertices[i].Set(point.x() / scaleRatio, -point.y() / scaleRatio);
        if(i > 0) {
            if(b2DistanceSquared(vertices[i - 1], vertices[i]) <= b2_linearSlop * b2_linearSlop)
            {
                qWarning() << "Chain: vertices are too close together";
                return 0;
            }
        }
    }

    b2ChainShape *shape = new b2ChainShape;
    if(mLoop) shape->CreateLoop(vertices, count);
    else shape->CreateChain(vertices, count);
    if(prevVertexFlag) shape->SetPrevVertex(b2Vec2(mPrevVertex.x() / scaleRatio,mPrevVertex.y() / scaleRatio));
    if(nextVertexFlag) shape->SetNextVertex(b2Vec2(mNextVertex.x() / scaleRatio,mNextVertex.y() / scaleRatio));
    delete[] vertices;
    return shape;
}

void Box2DChain::scale()
{
    if(mFixture)
    {
        b2Vec2 *vertices = scaleVertices();
        b2ChainShape *shape = new b2ChainShape;
        if(mLoop) shape->CreateLoop(vertices, mVertices.count());
        else shape->CreateChain(vertices, mVertices.count());
        delete[] vertices;
        applyShape(shape);
    }
}

//=================== EDGE =======================

b2Shape *Box2DEdge::createShape()
{
    const int count = mVertices.length();
    if (count != 2) {
        qWarning() << "Edge: Invalid number of vertices:" << count;
        return 0;
    }
    QPointF point1 = mVertices.at(0).toPointF();
    QPointF point2 = mVertices.at(1).toPointF();
    b2Vec2 vertex1(point1.x() / scaleRatio, -point1.y() / scaleRatio);
    b2Vec2 vertex2(point2.x() / scaleRatio, -point2.y() / scaleRatio);
    if(b2DistanceSquared(vertex1, vertex2) <= b2_linearSlop * b2_linearSlop)
    {
        qWarning() << "Edge: vertices are too close together";
        return 0;
    }
    b2EdgeShape *shape = new b2EdgeShape;
    shape->Set(vertex1,vertex2);

    return shape;
}

void Box2DEdge::scale()
{
    if(mFixture)
    {
        b2Vec2 *vertices = scaleVertices();
        b2EdgeShape *shape = new b2EdgeShape;
        shape->Set(vertices[0],vertices[1]);
        delete[] vertices;
        applyShape(shape);
    }
}
