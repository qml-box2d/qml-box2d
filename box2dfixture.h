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

#ifndef BOX2DFIXTURE_H
#define BOX2DFIXTURE_H

#include <QDeclarativeItem>
#include <QFlags>
#include <Box2D.h>

#include "box2dfixture.h"

class b2Body;
class b2Fixture;
class b2FixtureDef;
class b2Shape;

class Box2DFixture : public QDeclarativeItem
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

    explicit Box2DFixture(QDeclarativeItem *parent = 0);

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

protected:
    virtual b2Shape *createShape() = 0;

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

    b2FixtureDef mFixtureDef;
    b2Fixture *mFixture;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Box2DFixture::CategoryFlags)

class Box2DBox : public Box2DFixture
{
    Q_OBJECT

public:
    explicit Box2DBox(QDeclarativeItem *parent = 0) :
        Box2DFixture(parent)
    { }

protected:
    b2Shape *createShape();
};

class Box2DCircle : public Box2DFixture
{
    Q_OBJECT

    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    explicit Box2DCircle(QDeclarativeItem *parent = 0) :
        Box2DFixture(parent)
    { }

    float radius() const { return mRadius; }
    void setRadius(float radius) {
        if (mRadius == radius)
            return;
        mRadius = radius;
        emit radiusChanged();
    }

signals:
    void radiusChanged();

protected:
    b2Shape *createShape();

private:
    float mRadius;
};

class Box2DPolygon : public Box2DFixture
{
    Q_OBJECT

    Q_PROPERTY(QVariantList vertices READ vertices WRITE setVertices NOTIFY verticesChanged)

public:
    explicit Box2DPolygon(QDeclarativeItem *parent = 0) :
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
    b2Shape *createShape();

private:
    QVariantList mVertices;
};

#endif // BOX2DFIXTURE_H
