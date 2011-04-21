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

#include <QObject>
#include <QPointF>
#include <Box2D.h>

class b2World;
class Box2DBody;
class Box2DWorld;

class Box2DJoint : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)
    Q_PROPERTY(Box2DWorld *world READ box2DWorld WRITE setWorld NOTIFY worldChanged)
    Q_PROPERTY(Box2DBody *bodyA READ bodyA WRITE setBodyA NOTIFY bodyAChanged)
    Q_PROPERTY(Box2DBody *bodyB READ bodyB WRITE setBodyB NOTIFY bodyBChanged)

public:
    explicit Box2DJoint(QObject *parent = 0);

    bool collideConnected() const;
    void setCollideConnected(bool collideConnected);

    Box2DWorld *box2DWorld() const;
    void setWorld(Box2DWorld *world);

    Box2DBody *bodyA() const;
    void setBodyA(Box2DBody *bodyA);

    Box2DBody *bodyB() const;
    void setBodyB(Box2DBody *bodyB);

    void initialize();

    virtual void nullifyJoint() = 0;
    virtual void cleanup(b2World *world) = 0;

protected:
    virtual void createJoint() = 0;
    b2World *world() const;

private slots:
    void bodyACreated();
    void bodyBCreated();

signals:
    void collideConnectedChanged();
    void worldChanged();
    void bodyAChanged();
    void bodyBChanged();

protected:
    bool mInitializePending;

private:
    Box2DWorld *mWorld;
    bool mCollideConnected;
    Box2DBody *mBodyA;
    Box2DBody *mBodyB;
};


/**
 * Convenience function to get the Box2DJoint wrapping a b2Joint.
 */
inline Box2DJoint *toBox2DJoint(b2Joint *joint)
{
    return static_cast<Box2DJoint*>(joint->GetUserData());
}


#endif // BOX2DJOINT_H
