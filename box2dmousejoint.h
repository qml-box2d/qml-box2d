/*
 * box2dmousejoint.h
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

#ifndef BOX2DMOUSEJOINT_H
#define BOX2DMOUSEJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2MouseJoint;
class b2MouseJointDef;

class Box2DMouseJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QPointF target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float maxForce READ maxForce WRITE setMaxForce NOTIFY maxForceChanged)
    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)

public:
    explicit Box2DMouseJoint(QObject *parent = 0);
    ~Box2DMouseJoint();

    float dampingRatio() const;
    void setDampingRatio(float dampingRatio);

    float frequencyHz() const;
    void setFrequencyHz(float frequencyHz);

    float maxForce() const;
    void setMaxForce(float maxForce);

    QPointF target() const;
    void setTarget(const QPointF &_target);

    Q_INVOKABLE QPointF GetReactionForce(float32 inv_dt) const;
    Q_INVOKABLE float GetReactionTorque(float32 inv_dt) const;

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);
    b2Joint * GetJoint();

signals:
    void targetChanged();
    void maxForceChanged();
    void frequencyHzChanged();
    void dampingRatioChanged();

private:
    b2MouseJointDef mMouseJointDef;
    b2MouseJoint *mMouseJoint;
};



#endif // BOX2DMOUSEJOINT_H
