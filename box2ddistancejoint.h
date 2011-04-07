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

#ifndef BOX2DDISTANCEJOINT_H
#define BOX2DDISTANCEJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2DistanceJoint;
class b2DistanceJointDef;

class Box2DDistanceJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float length READ length WRITE setLength NOTIFY lengthChanged)
    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)

public:
    explicit Box2DDistanceJoint(QObject *parent = 0);
    ~Box2DDistanceJoint();

    float length() const;
    void setLength(float length);

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

signals:
    void lengthChanged();
    void frequencyHzChanged();
    void dampingRatioChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();

private:
    b2DistanceJointDef mDistanceJointDef;
    b2DistanceJoint *mDistanceJoint;
    bool mOverrideAnchorLength;
    float mLength;
    bool mOverrideLocalAnchorA;
    QPointF mLocalAnchorA;
    bool mOverrideLocalAnchorB;
    QPointF mLocalAnchorB;
};

#endif // BOX2DDISTANCEJOINT_H
