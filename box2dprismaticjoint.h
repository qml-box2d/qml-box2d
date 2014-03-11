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
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)


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

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    Q_INVOKABLE float GetJointTranslation();
    Q_INVOKABLE float GetJointSpeed();

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);
    b2Joint * GetJoint();

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
    bool anchorsAuto;
};



#endif // BOX2DPRISMATICJOINT_H
