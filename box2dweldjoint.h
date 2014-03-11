/*
 * box2ddistancejoint.h
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

#ifndef BOX2WELDJOINT_H
#define BOX2WELDJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2WeldJoint;
class b2WeldJointDef;

class Box2DWeldJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float referenceAngle READ referenceAngle WRITE setReferenceAngle NOTIFY referenceAngleChanged)
    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)

public:
    explicit Box2DWeldJoint(QObject *parent = 0);
    ~Box2DWeldJoint();

    float referenceAngle() const;
    void setReferenceAngle(float referenceAngle);

    float frequencyHz() const;
    void setFrequencyHz(float frequencyHz);

    float dampingRatio() const;
    void setDampingRatio(float dampingRatio);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);
    b2Joint * GetJoint();

signals:
    void referenceAngleChanged();
    void frequencyHzChanged();
    void dampingRatioChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();

private:
    b2WeldJointDef mWeldJointDef;
    b2WeldJoint * mWeldJoint;
    bool anchorsAuto;
};

#endif // BOX2WELDJOINT_H
