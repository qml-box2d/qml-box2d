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

#ifndef BOX2DREVOLUTEJOINT_H
#define BOX2DREVOLUTEJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2RevoluteJoint;
class b2RevoluteJointDef;

class Box2DRevoluteJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float lowerAngle READ lowerAngle WRITE setLowerAngle NOTIFY lowerAngleChanged)
    Q_PROPERTY(float upperAngle READ upperAngle WRITE setUpperAngle NOTIFY upperAngleChanged)
    Q_PROPERTY(float maxMotorTorque READ maxMotorTorque WRITE setMaxMotorTorque NOTIFY maxMotorTorqueChanged)
    Q_PROPERTY(float motorSpeed READ motorSpeed WRITE setMotorSpeed NOTIFY motorSpeedChanged)
    Q_PROPERTY(bool enableLimit READ enableLimit WRITE setEnableLimit NOTIFY enableLimitChanged)
    Q_PROPERTY(bool enableMotor READ enableMotor WRITE setEnableMotor NOTIFY enableMotorChanged)
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)

public:
    explicit Box2DRevoluteJoint(QObject *parent = 0);
    ~Box2DRevoluteJoint();

    float lowerAngle() const;
    void setLowerAngle(float lowerAngle);

    float upperAngle() const;
    void setUpperAngle(float upperAngle);

    float maxMotorTorque() const;
    void setMaxMotorTorque(float maxMotorTorque);

    float motorSpeed() const;
    void setMotorSpeed(float motorSpeed);

    bool enableLimit() const;
    void setEnableLimit(bool enableLimit);

    bool enableMotor() const;
    void setEnableMotor(bool enableMotor);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);

signals:
    void lowerAngleChanged();
    void upperAngleChanged();
    void maxMotorTorqueChanged();
    void motorSpeedChanged();
    void enableLimitChanged();
    void enableMotorChanged();
    void localAnchorAChanged();

private:
    b2RevoluteJointDef mRevoluteJointDef;
    b2RevoluteJoint *mRevoluteJoint;
    bool mOverrideLocalAnchorA;
    QPointF mLocalAnchorA;
};

#endif // BOX2DREVOLUTEJOINT_H
