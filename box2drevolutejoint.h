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

class Box2DRevoluteJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)
    Q_PROPERTY(float referenceAngle READ referenceAngle WRITE setReferenceAngle NOTIFY referenceAngleChanged)
    Q_PROPERTY(bool enableLimit READ enableLimit WRITE setEnableLimit NOTIFY enableLimitChanged)
    Q_PROPERTY(float lowerAngle READ lowerAngle WRITE setLowerAngle NOTIFY lowerAngleChanged)
    Q_PROPERTY(float upperAngle READ upperAngle WRITE setUpperAngle NOTIFY upperAngleChanged)
    Q_PROPERTY(bool enableMotor READ enableMotor WRITE setEnableMotor NOTIFY enableMotorChanged)
    Q_PROPERTY(float motorSpeed READ motorSpeed WRITE setMotorSpeed NOTIFY motorSpeedChanged)
    Q_PROPERTY(float maxMotorTorque READ maxMotorTorque WRITE setMaxMotorTorque NOTIFY maxMotorTorqueChanged)

public:
    explicit Box2DRevoluteJoint(QObject *parent = 0);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    float referenceAngle() const;
    void setReferenceAngle(float referenceAngle);

    bool enableLimit() const;
    void setEnableLimit(bool enableLimit);

    float lowerAngle() const;
    void setLowerAngle(float lowerAngle);

    float upperAngle() const;
    void setUpperAngle(float upperAngle);

    bool enableMotor() const;
    void setEnableMotor(bool enableMotor);

    float motorSpeed() const;
    void setMotorSpeed(float motorSpeed);

    float maxMotorTorque() const;
    void setMaxMotorTorque(float maxMotorTorque);

    b2RevoluteJoint *revoluteJoint() const;

    Q_INVOKABLE float getJointAngle() const;
    Q_INVOKABLE float getJointSpeed() const;

signals:
    void localAnchorAChanged();
    void localAnchorBChanged();
    void referenceAngleChanged();
    void enableLimitChanged();
    void lowerAngleChanged();
    void upperAngleChanged();
    void enableMotorChanged();
    void motorSpeedChanged();
    void maxMotorTorqueChanged();

protected:
    b2Joint *createJoint();

private:
    QPointF m_localAnchorA;
    QPointF m_localAnchorB;
    float m_referenceAngle;
    bool m_enableLimit;
    float m_lowerAngle;
    float m_upperAngle;
    bool m_enableMotor;
    float m_motorSpeed;
    float m_maxMotorTorque;
    bool m_defaultLocalAnchorA;
    bool m_defaultLocalAnchorB;
    bool m_defaultReferenceAngle;
};

inline QPointF Box2DRevoluteJoint::localAnchorA() const
{
    return m_localAnchorA;
}

inline QPointF Box2DRevoluteJoint::localAnchorB() const
{
    return m_localAnchorB;
}

inline float Box2DRevoluteJoint::referenceAngle() const
{
    return m_referenceAngle;
}

inline float Box2DRevoluteJoint::lowerAngle() const
{
    return m_lowerAngle;
}

inline float Box2DRevoluteJoint::upperAngle() const
{
    return m_upperAngle;
}

inline float Box2DRevoluteJoint::maxMotorTorque() const
{
    return m_maxMotorTorque;
}

inline float Box2DRevoluteJoint::motorSpeed() const
{
    return m_motorSpeed;
}

inline bool Box2DRevoluteJoint::enableLimit() const
{
    return m_enableLimit;
}

inline bool Box2DRevoluteJoint::enableMotor() const
{
    return m_enableMotor;
}

inline b2RevoluteJoint *Box2DRevoluteJoint::revoluteJoint() const
{
    return static_cast<b2RevoluteJoint*>(joint());
}

#endif // BOX2DREVOLUTEJOINT_H
