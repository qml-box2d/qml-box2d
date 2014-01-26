/*
 * box2drevolutejoint.h
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2011 Markus Kivioja <markus.kivioja@digia.com>
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
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)

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

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);
    b2Joint * GetJoint();

    Q_INVOKABLE float getJointAngle();
    Q_INVOKABLE float getJointSpeed();

signals:
    void lowerAngleChanged();
    void upperAngleChanged();
    void maxMotorTorqueChanged();
    void motorSpeedChanged();
    void enableLimitChanged();
    void enableMotorChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();

private:
    b2RevoluteJointDef mRevoluteJointDef;
    b2RevoluteJoint *mRevoluteJoint;
    bool anchorsAuto;
};

#endif // BOX2DREVOLUTEJOINT_H
