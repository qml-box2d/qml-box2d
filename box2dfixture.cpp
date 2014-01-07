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

void Box2DFixture::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    qreal nw = newGeometry.right();
    qreal nh = newGeometry.bottom();
    qreal ow = oldGeometry.right();
    qreal oh = oldGeometry.bottom();

    if((nw != ow && !qFuzzyCompare(ow,0.0)) ||  (nh != oh && !qFuzzyCompare(oh,0.0)) )
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

void Box2DFixture::scaleVertices()
{
    b2PolygonShape * shape = static_cast<b2PolygonShape *>(mFixture->GetShape());
    if(shape)
    {
        b2PolygonShape newShape;
        b2Vec2 * vertices = new b2Vec2[shape->GetVertexCount()];
        for(int i = 0;i < shape->GetVertexCount();i ++)
        {
            b2Vec2 vertex = shape->GetVertex(i);
            vertices[i].x = vertex.x * factorWidth;
            vertices[i].y = vertex.y * factorHeight;
        }
        newShape.Set(vertices,shape->GetVertexCount());
        mBody->DestroyFixture(mFixture);
        mFixtureDef.shape = &newShape;
        mFixture = mBody->CreateFixture(&mFixtureDef);
        mFixture->SetUserData(this);
    }
}


void Box2DBox::scale()
{
    if(mFixture)
        scaleVertices();
}

b2Shape *Box2DBox::createShape()
{

    const qreal _x = x() / scaleRatio;
    const qreal _y = -y() / scaleRatio;
    b2Vec2 vertices[4];
    vertices[0].Set(_x, _y);
    vertices[1].Set(_x, _y - height() / scaleRatio);
    vertices[2].Set(_x + width() / scaleRatio, _y - height() / scaleRatio);
    vertices[3].Set(_x + width() / scaleRatio, _y);

    int32 count = 4;
    b2PolygonShape *shape = new b2PolygonShape;
    shape->Set(vertices, count);
    return shape;
}

void Box2DCircle::scale()
{
    if(mFixture)
    {
        b2Shape * newShape = createShape();
        mBody->DestroyFixture(mFixture);
        mFixtureDef.shape = newShape;
        mFixture = mBody->CreateFixture(&mFixtureDef);
        mFixture->SetUserData(this);
        delete newShape;
    }
}

b2Shape *Box2DCircle::createShape()
{
    b2CircleShape *shape = new b2CircleShape;
    shape->m_radius = mRadius / scaleRatio;
    shape->m_p.Set(x() / scaleRatio, -y() / scaleRatio);
    return shape;
}


void Box2DPolygon::scale()
{

    if(mFixture)
        scaleVertices();

}

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
    }

    b2PolygonShape *shape = new b2PolygonShape;
    shape->Set(vertices, count);
    delete[] vertices;
    return shape;
}
