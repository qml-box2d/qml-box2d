/*
 * box2dfixture.h
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

#ifndef BOX2DFIXTURE_H
#define BOX2DFIXTURE_H

#include <QQuickItem>
#include <QFlags>
#include <Box2D.h>

#include "box2dfixture.h"

class b2Body;
class b2Fixture;
struct b2FixtureDef;
class b2Shape;
class Box2DBody;

class Box2DFixture : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(float density READ density WRITE setDensity NOTIFY densityChanged)
    Q_PROPERTY(float friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(float restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(bool sensor READ isSensor WRITE setSensor NOTIFY sensorChanged)
    Q_PROPERTY(CategoryFlags categories READ categories WRITE setCategories NOTIFY categoriesChanged)
    Q_PROPERTY(CategoryFlags collidesWith READ collidesWith WRITE setCollidesWith NOTIFY collidesWithChanged)
    Q_PROPERTY(int groupIndex READ groupIndex WRITE setGroupIndex NOTIFY groupIndexChanged)

    Q_ENUMS(CategoryFlag)
    Q_FLAGS(CategoryFlags)

public:

    explicit Box2DFixture(QQuickItem *parent = 0);

    enum CategoryFlag {Category1 = 0x0001, Category2 = 0x0002, Category3 = 0x0004, Category4 = 0x0008,
                       Category5 = 0x0010, Category6 = 0x0020, Category7 = 0x0040, Category8 = 0x0080,
                       Category9 = 0x0100, Category10 = 0x0200, Category11 = 0x0400, Category12 = 0x0800,
                       Category13 = 0x1000, Category14 = 0x2000, Category15 = 0x4000, Category16 = 0x8000,
                       All = 0xFFFF, None=0x0000};

    Q_DECLARE_FLAGS(CategoryFlags, CategoryFlag)

    float density() const;
    void setDensity(float density);

    float friction() const;
    void setFriction(float friction);

    float restitution() const;
    void setRestitution(float restitution);

    bool isSensor() const;
    void setSensor(bool sensor);

    CategoryFlags categories() const;
    void setCategories(CategoryFlags layers);

    CategoryFlags collidesWith() const;
    void setCollidesWith(CategoryFlags layers);

    int groupIndex() const;
    void setGroupIndex(int groupIndex);

    void createFixture(b2Body *body);
    virtual void scale(){}

    Q_INVOKABLE Box2DBody * GetBody() const;

protected:
    b2Fixture *mFixture;
    b2FixtureDef mFixtureDef;
    b2Body * mBody;
    float factorWidth;
    float factorHeight;
    virtual b2Shape *createShape() = 0;
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);
    void applyShape(b2Shape * shape);

signals:
    void densityChanged();
    void frictionChanged();
    void restitutionChanged();
    void sensorChanged();
    void categoriesChanged();
    void collidesWithChanged();
    void groupIndexChanged();

    void beginContact(Box2DFixture *other);
    void contactChanged(Box2DFixture *other);
    void endContact(Box2DFixture *other);


private:
    friend class Box2DWorld;

    void emitBeginContact(Box2DFixture *other);
    void emitContactChanged(Box2DFixture *other);
    void emitEndContact(Box2DFixture *other);




};

Q_DECLARE_OPERATORS_FOR_FLAGS(Box2DFixture::CategoryFlags)

class Box2DBox : public Box2DFixture
{
    Q_OBJECT

public:
    explicit Box2DBox(QQuickItem *parent = 0) :
        Box2DFixture(parent)
    { }
    void scale();

protected:
    b2Shape *createShape();
    b2Vec2 vertices[4];
};


class Box2DCircle : public Box2DFixture
{
    Q_OBJECT

    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    explicit Box2DCircle(QQuickItem *parent = 0) :
        Box2DFixture(parent)
    { }

    float radius() const { return mRadius; }
    void setRadius(float radius) {
        if (mRadius == radius)
            return;
        mRadius = radius;
        scale();
        emit radiusChanged();
    }
    void scale();
signals:
    void radiusChanged();

protected:
    b2Shape *createShape();

private:
    float mRadius;
};


class Box2DVerticesShape : public Box2DFixture
{
    Q_OBJECT
    Q_PROPERTY(QVariantList vertices READ vertices WRITE setVertices NOTIFY verticesChanged)
public:
    explicit Box2DVerticesShape(QQuickItem *parent = 0) :
        Box2DFixture(parent)
    { }
    QVariantList vertices() const { return mVertices; }
    void setVertices(const QVariantList &vertices) {
        if (vertices == mVertices)
            return;
        mVertices = vertices;
        emit verticesChanged();
    }
signals:
    void verticesChanged();

protected:
    QVariantList mVertices;
    b2Vec2 * scaleVertices();
    virtual b2Shape *createShape(){ return NULL; }
};

class Box2DPolygon : public Box2DVerticesShape
{
public:
    explicit Box2DPolygon(QQuickItem *parent = 0) :
        Box2DVerticesShape(parent)
    { }
    void scale();

protected:
    b2Shape *createShape();
};


class Box2DChain : public Box2DVerticesShape
{
    Q_OBJECT
    Q_PROPERTY(bool loop READ loop WRITE setLoop NOTIFY loopChanged)
    Q_PROPERTY(QPointF prevVertex READ prevVertex WRITE setPrevVertex NOTIFY prevVertexChanged)
    Q_PROPERTY(QPointF nextVertex READ nextVertex WRITE setNextVertex NOTIFY nextVertexChanged)
public:
    explicit Box2DChain(QQuickItem *parent = 0) :
        Box2DVerticesShape(parent),
        mLoop(false)
    { }
    void scale();
    bool loop() const { return mLoop; }
    void setLoop(bool loop) {
        mLoop = loop;
        emit loopChanged();
    }
    QPointF prevVertex() const { return mPrevVertex; }
    void setPrevVertex(QPointF &prevVertex) {
        mPrevVertex = prevVertex;
        prevVertexFlag = true;
    }
    QPointF nextVertex() const { return mNextVertex; }
    void setNextVertex(QPointF &nextVertex) {
        mNextVertex = nextVertex;
        nextVertexFlag = true;
    }

protected:
    b2Shape *createShape();
    bool mLoop;
    bool prevVertexFlag;
    bool nextVertexFlag;
    QPointF mPrevVertex;
    QPointF mNextVertex;
signals:
    void loopChanged();
    void prevVertexChanged();
    void nextVertexChanged();
};

class Box2DEdge : public Box2DVerticesShape
{
    Q_OBJECT
public:
    explicit Box2DEdge(QQuickItem *parent = 0) :
        Box2DVerticesShape(parent)
    { }
    void scale();

protected:
    b2Shape *createShape();

};

/**
 * Convenience function to get the Box2DFixture wrapping a b2Fixture.
 */
inline Box2DFixture *toBox2DFixture(b2Fixture *fixture)
{
    return static_cast<Box2DFixture*>(fixture->GetUserData());
}


#endif // BOX2DFIXTURE_H
