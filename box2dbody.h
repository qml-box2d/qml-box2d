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

#ifndef BOX2DBODY_H
#define BOX2DBODY_H

#include <QDeclarativeItem>

class Box2DWorld;

class b2Body;
class b2World;

/**
 * The Box2D body, build up from a list of shapes.
 */
class Box2DBody : public QDeclarativeItem
{
    Q_OBJECT

    Q_ENUMS(BodyType);
    Q_PROPERTY(BodyType bodyType READ bodyType WRITE setBodyType NOTIFY bodyTypeChanged)
    Q_PROPERTY(bool sleepingAllowed READ sleepingAllowed WRITE setSleepingAllowed NOTIFY sleepingAllowedChanged)

public:
    enum BodyType {
        Static,
        Kinematic,
        Dynamic
    };

    explicit Box2DBody(QDeclarativeItem *parent = 0);
    ~Box2DBody();

    BodyType bodyType() const { return mBodyType; }
    void setBodyType(BodyType bodyType);

    bool sleepingAllowed() const { return mSleepingAllowed; }
    void setSleepingAllowed(bool allowed);

    void initialize(b2World *world);
    void synchronize();
    void cleanup(b2World *world);

signals:
    void bodyTypeChanged();
    void sleepingAllowedChanged();

private:
    b2Body *mBody;
    BodyType mBodyType;
    bool mSleepingAllowed;
};

#endif // BOX2DBODY_H
