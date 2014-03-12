/*
 * box2dprismaticjoint.h
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
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

#ifndef BOX2FRICTIONJOINT_H
#define BOX2FRICTIONJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2FrictionJoint;
class b2FrictionJointDef;

class Box2DFrictionJoint : public Box2DJoint
{
    Q_OBJECT
    Q_PROPERTY(float maxForce READ maxForce WRITE setMaxForce NOTIFY maxForceChanged)
    Q_PROPERTY(float maxTorque READ maxTorque WRITE setMaxTorque NOTIFY maxTorqueChanged)
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)

public:
    explicit Box2DFrictionJoint(QObject *parent = 0);
    ~Box2DFrictionJoint();

    float maxForce() const;
    void setMaxForce(float maxForce);

    float maxTorque() const;
    void setMaxTorque(float maxTorque);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);
    b2Joint * GetJoint();

    Q_INVOKABLE QPointF GetReactionForce(float32 inv_dt) const;
    Q_INVOKABLE float GetReactionTorque(float32 inv_dt) const;

signals:
    void maxForceChanged();
    void maxTorqueChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();

private:
    b2FrictionJointDef mFrictionJointDef;
    b2FrictionJoint * mFrictionJoint;
    bool anchorsAuto;
};



#endif // BOX2FRICTIONJOINT_H
