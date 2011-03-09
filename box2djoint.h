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

#ifndef BOX2DJOINT_H
#define BOX2DJOINT_H

#include <QDeclarativeItem>
#include <Box2D.h>

class b2World;
class Box2DBody;

class Box2DJoint : public QDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)
    Q_PROPERTY(Box2DBody *bodyA READ bodyA WRITE setBodyA NOTIFY bodyAChanged)
    Q_PROPERTY(Box2DBody *bodyB READ bodyB WRITE setBodyB NOTIFY bodyBChanged)

public:
    explicit Box2DJoint(QDeclarativeItem *parent = 0);

    bool collideConnected() const;
    void setCollideConnected(bool collideConnected);

    Box2DBody *bodyA() const;
    void setBodyA(Box2DBody *bodyA);

    Box2DBody *bodyB() const;
    void setBodyB(Box2DBody *bodyB);

    void initialize(b2World *world);
    void componentComplete();

    virtual void cleanup(b2World *world) = 0;

protected:
    virtual void createJoint() = 0;
    b2World *world() const;

signals:
    void collideConnectedChanged();
    void bodyAChanged();
    void bodyBChanged();

protected:
    bool mInitializePending;

private:
    b2World *mWorld;
    bool mCollideConnected;
    Box2DBody* mBodyA;
    Box2DBody* mBodyB;
};

#endif // BOX2DJOINT_H
