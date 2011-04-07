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

#ifndef BOX2DPRISMATICJOINT_H
#define BOX2DPRISMATICJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2PrismaticJoint;
class b2PrismaticJointDef;

class Box2DPrismaticJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float lowerTranslation READ lowerTranslation WRITE setLowerTranslation NOTIFY lowerTranslationChanged)
    Q_PROPERTY(float upperTranslation READ upperTranslation WRITE setUpperTranslation NOTIFY upperTranslationChanged)
    Q_PROPERTY(float maxMotorForce READ maxMotorForce WRITE setMaxMotorForce NOTIFY maxMotorForceChanged)
    Q_PROPERTY(float motorSpeed READ motorSpeed WRITE setMotorSpeed NOTIFY motorSpeedChanged)
    Q_PROPERTY(bool enableLimit READ enableLimit WRITE setEnableLimit NOTIFY enableLimitChanged)
    Q_PROPERTY(bool enableMotor READ enableMotor WRITE setEnableMotor NOTIFY enableMotorChanged)
    Q_PROPERTY(QPointF axis READ axis WRITE setAxis NOTIFY axisChanged)

public:
    explicit Box2DPrismaticJoint(QObject *parent = 0);
    ~Box2DPrismaticJoint();

    float lowerTranslation() const;
    void setLowerTranslation(float lowerTranslation);

    float upperTranslation() const;
    void setUpperTranslation(float upperTranslation);

    float maxMotorForce() const;
    void setMaxMotorForce(float maxMotorForce);

    float motorSpeed() const;
    void setMotorSpeed(float motorSpeed);

    bool enableLimit() const;
    void setEnableLimit(bool enableLimit);

    bool enableMotor() const;
    void setEnableMotor(bool enableMotor);

    QPointF axis() const;
    void setAxis(const QPointF &axis);

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);

signals:
    void lowerTranslationChanged();
    void upperTranslationChanged();
    void maxMotorForceChanged();
    void motorSpeedChanged();
    void enableLimitChanged();
    void enableMotorChanged();
    void axisChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();

private:
    b2PrismaticJointDef mPrismaticJointDef;
    b2PrismaticJoint *mPrismaticJoint;
};

#endif // BOX2DPRISMATICJOINT_H
