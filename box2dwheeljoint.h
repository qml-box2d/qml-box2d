/*
 * box2dwheeljoint.h
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

#ifndef BOX2DWHEELJOINT_H
#define BOX2DWHEELJOINT_H

#include "box2djoint.h"
#include <box2d/box2d.h>

class Box2DWheelJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)
    Q_PROPERTY(QPointF localAxisA READ localAxisA WRITE setLocalAxisA NOTIFY localAxisAChanged)
    Q_PROPERTY(float damping READ damping WRITE setDamping NOTIFY dampingChanged)
    Q_PROPERTY(float stiffness READ stiffness WRITE setStiffness NOTIFY stiffnessChanged)
    Q_PROPERTY(float maxMotorTorque READ maxMotorTorque WRITE setMaxMotorTorque NOTIFY maxMotorTorqueChanged)
    Q_PROPERTY(float motorSpeed READ motorSpeed WRITE setMotorSpeed NOTIFY motorSpeedChanged)
    Q_PROPERTY(bool enableMotor READ enableMotor WRITE setEnableMotor NOTIFY enableMotorChanged)

public:
    explicit Box2DWheelJoint(QObject *parent = nullptr);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    QPointF localAxisA() const;
    void setLocalAxisA(const QPointF &localAxisA);

    bool enableMotor() const;
    void setEnableMotor(bool enableMotor);

    float maxMotorTorque() const;
    void setMaxMotorTorque(float maxMotorTorque);

    float motorSpeed() const;
    void setMotorSpeed(float motorSpeed);

    float stiffness() const;
    void setStiffness(float stiffness);

    float damping() const;
    void setDamping(float damping);

    b2WheelJoint *wheelJoint() const;

    Q_INVOKABLE QPointF getReactionForce(float inv_dt) const;
    Q_INVOKABLE float getReactionTorque(float inv_dt) const;
    Q_INVOKABLE float getJointTranslation() const;
    Q_INVOKABLE float getJointSpeed() const;

signals:
    void localAnchorAChanged();
    void localAnchorBChanged();
    void localAxisAChanged();
    void enableMotorChanged();
    void maxMotorTorqueChanged();
    void motorSpeedChanged();
    void stiffnessChanged();
    void dampingChanged();

protected:
    b2Joint *createJoint() override;

private:
    QPointF m_localAnchorA;
    QPointF m_localAnchorB;
    QPointF m_localAxisA;
    bool m_enableMotor;
    float m_maxMotorTorque;
    float m_motorSpeed;
    float m_stiffness;
    float m_damping;

    bool m_defaultLocalAnchorA;
    bool m_defaultLocalAnchorB;
    bool m_defaultLocalAxisA;
};

inline QPointF Box2DWheelJoint::localAnchorA() const
{
    return m_localAnchorA;
}

inline QPointF Box2DWheelJoint::localAnchorB() const
{
    return m_localAnchorB;
}

inline QPointF Box2DWheelJoint::localAxisA() const
{
    return m_localAxisA;
}

inline bool Box2DWheelJoint::enableMotor() const
{
    return m_enableMotor;
}

inline float Box2DWheelJoint::maxMotorTorque() const
{
    return m_maxMotorTorque;
}

inline float Box2DWheelJoint::motorSpeed() const
{
    return m_motorSpeed;
}

inline float Box2DWheelJoint::stiffness() const
{
    return m_stiffness;
}

inline float Box2DWheelJoint::damping() const
{
    return m_damping;
}

inline b2WheelJoint *Box2DWheelJoint::wheelJoint() const
{
    return static_cast<b2WheelJoint*>(joint());
}

#endif // BOX2DWHEELJOINT_H
