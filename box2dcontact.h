/*
 * box2dcontact.h
 * Copyright (c) 2014 Moukhlynin Ruslan <ruslan@khvmntk.ru>
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

#ifndef BOX2DCONTACT_H
#define BOX2DCONTACT_H

#include <QObject>
#include <Box2D.h>

class Box2DFixture;

class Box2DContact : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(Box2DFixture *fixtureA READ fixtureA)
    Q_PROPERTY(Box2DFixture *fixtureB READ fixtureB)
    Q_PROPERTY(int childIndexA READ childIndexA)
    Q_PROPERTY(int childIndexB READ childIndexB)
    Q_PROPERTY(qreal friction READ getFriction WRITE setFriction)
    Q_PROPERTY(qreal restitution READ getRestitution WRITE setRestitution)
    Q_PROPERTY(qreal tangentSpeed READ getTangentSpeed WRITE setTangentSpeed)

public:
    Box2DContact(b2Contact *contact = 0);
    void setContact(b2Contact *contact);

    Q_INVOKABLE bool isTouching();
    Q_INVOKABLE void resetFriction();
    Q_INVOKABLE void resetRestitution();

protected:
    b2Contact *mContact;

    bool isEnabled() const;
    void setEnabled(bool enabled);

    Box2DFixture *fixtureA() const;
    Box2DFixture *fixtureB() const;

    int childIndexA() const;
    int childIndexB() const;

    qreal getFriction() const;
    void setFriction(qreal friction);

    qreal getRestitution() const;
    void setRestitution(qreal restitution);

    qreal getTangentSpeed() const;
    void setTangentSpeed(qreal speed);
};

#endif // BOX2DCONTACT_H
