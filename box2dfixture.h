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

class Box2DBody;

class Box2DFixture : public QObject
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
    explicit Box2DFixture(QObject *parent = 0);

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

    void initialize(Box2DBody *body);
    void recreateFixture();

    Q_INVOKABLE Box2DBody *getBody() const;

signals:
    void densityChanged();
    void frictionChanged();
    void restitutionChanged();
    void sensorChanged();
    void categoriesChanged();
    void collidesWithChanged();
    void groupIndexChanged();

    void beginContact(Box2DFixture *other);
    void endContact(Box2DFixture *other);

protected:
    virtual b2Shape *createShape() = 0;

    b2Fixture *mFixture;
    b2FixtureDef mFixtureDef;
    Box2DBody *mBody;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Box2DFixture::CategoryFlags)

class Box2DBox : public Box2DFixture
{
    Q_OBJECT

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)

public:
    explicit Box2DBox(QQuickItem *parent = 0)
        : Box2DFixture(parent)
        , mPosition(0, 0)
        , mSize(0, 0)
        , mRotation(0)
    {}

    qreal x() const { return mPosition.x(); }
    void setX(qreal x);

    qreal y() const { return mPosition.y(); }
    void setY(qreal y);

    qreal width() const { return mSize.width(); }
    void setWidth(qreal width);

    qreal height() const { return mSize.height(); }
    void setHeight(qreal height);

    qreal rotation() const { return mRotation; }
    void setRotation(qreal rotation);

signals:
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void rotationChanged();

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    b2Shape *createShape();

private:
    QPointF mPosition;
    QSizeF mSize;
    qreal mRotation;
};


class Box2DCircle : public Box2DFixture
{
    Q_OBJECT

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    explicit Box2DCircle(QQuickItem *parent = 0)
        : Box2DFixture(parent)
        , mPosition(0, 0)
        , mRadius(32)
    { }

    qreal x() const { return mPosition.x(); }
    void setX(qreal x);

    qreal y() const { return mPosition.y(); }
    void setY(qreal y);

    QPointF position() const { return mPosition; }

    float radius() const { return mRadius; }
    void setRadius(float radius);

signals:
    void xChanged();
    void yChanged();
    void radiusChanged();

protected:
    b2Shape *createShape();

private:
    QPointF mPosition;
    float mRadius;
};


class Box2DPolygon : public Box2DFixture
{
    Q_OBJECT

    Q_PROPERTY(QVariantList vertices READ vertices WRITE setVertices NOTIFY verticesChanged)

public:
    explicit Box2DPolygon(QQuickItem *parent = 0) :
        Box2DFixture(parent)
    { }

    QVariantList vertices() const { return mVertices; }
    void setVertices(const QVariantList &vertices);

signals:
    void verticesChanged();

protected:
    b2Shape *createShape();

private:
    QVariantList mVertices;
};


class Box2DChain : public Box2DFixture
{
    Q_OBJECT

    Q_PROPERTY(QVariantList vertices READ vertices WRITE setVertices NOTIFY verticesChanged)
    Q_PROPERTY(bool loop READ loop WRITE setLoop NOTIFY loopChanged)
    Q_PROPERTY(QPointF prevVertex READ prevVertex WRITE setPrevVertex NOTIFY prevVertexChanged)
    Q_PROPERTY(QPointF nextVertex READ nextVertex WRITE setNextVertex NOTIFY nextVertexChanged)

public:
    explicit Box2DChain(QQuickItem *parent = 0);

    QVariantList vertices() const { return mVertices; }
    void setVertices(const QVariantList &vertices);

    bool loop() const { return mLoop; }
    void setLoop(bool loop);

    QPointF prevVertex() const { return mPrevVertex; }
    void setPrevVertex(const QPointF &prevVertex);

    QPointF nextVertex() const { return mNextVertex; }
    void setNextVertex(const QPointF &nextVertex);

signals:
    void verticesChanged();
    void loopChanged();
    void prevVertexChanged();
    void nextVertexChanged();

protected:
    b2Shape *createShape();

private:
    QVariantList mVertices;
    QPointF mPrevVertex;
    QPointF mNextVertex;
    bool mLoop;
    bool mPrevVertexFlag;
    bool mNextVertexFlag;
};


class Box2DEdge : public Box2DFixture
{
    Q_OBJECT

    Q_PROPERTY(QVariantList vertices READ vertices WRITE setVertices NOTIFY verticesChanged)

public:
    explicit Box2DEdge(QQuickItem *parent = 0) :
        Box2DFixture(parent)
    { }

    QVariantList vertices() const { return mVertices; }
    void setVertices(const QVariantList &vertices);

signals:
    void verticesChanged();

protected:
    b2Shape *createShape();

private:
    QVariantList mVertices;
};


/**
 * Convenience function to get the Box2DFixture wrapping a b2Fixture.
 */
inline Box2DFixture *toBox2DFixture(b2Fixture *fixture)
{
    return static_cast<Box2DFixture*>(fixture->GetUserData());
}


#endif // BOX2DFIXTURE_H
