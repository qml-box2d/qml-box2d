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

class b2Body;
class b2Shape;

class Box2DFixture : public QDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(float density READ density WRITE setDensity NOTIFY densityChanged)
    Q_PROPERTY(float friction READ friction WRITE setFriction NOTIFY frictionChanged)
    Q_PROPERTY(float restitution READ restitution WRITE setRestitution NOTIFY restitutionChanged)
    Q_PROPERTY(bool sensor READ isSensor WRITE setSensor NOTIFY sensorChanged)

public:
    explicit Box2DFixture(QDeclarativeItem *parent = 0);

    float density() const { return mDensity; }
    void setDensity(float density);

    float friction() const { return mFriction; }
    void setFriction(float friction);

    float restitution() const { return mRestitution; }
    void setRestitution(float restitution);

    bool isSensor() const { return mSensor; }
    void setSensor(bool sensor);

    void createFixture(b2Body *body);

protected:
    virtual b2Shape *createShape() = 0;

signals:
    void densityChanged();
    void frictionChanged();
    void restitutionChanged();
    void sensorChanged();

private:
    float mDensity;
    float mFriction;
    float mRestitution;
    bool mSensor;
};


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

#endif // BOX2DFIXTURE_H
