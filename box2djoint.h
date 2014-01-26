/*
 * box2djoint.h
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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
    virtual b2Joint * GetJoint() = 0;

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
    void created();

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
    if(!joint) return 0;
    return static_cast<Box2DJoint*>(joint->GetUserData());
}


#endif // BOX2DJOINT_H
