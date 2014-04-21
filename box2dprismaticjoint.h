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

class Box2DPrismaticJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)
    Q_PROPERTY(QPointF localAxisA READ localAxisA WRITE setLocalAxisA NOTIFY localAxisAChanged)
    Q_PROPERTY(float referenceAngle READ referenceAngle WRITE setReferenceAngle NOTIFY referenceAngleChanged)
    Q_PROPERTY(bool enableLimit READ enableLimit WRITE setEnableLimit NOTIFY enableLimitChanged)
    Q_PROPERTY(float lowerTranslation READ lowerTranslation WRITE setLowerTranslation NOTIFY lowerTranslationChanged)
    Q_PROPERTY(float upperTranslation READ upperTranslation WRITE setUpperTranslation NOTIFY upperTranslationChanged)
    Q_PROPERTY(bool enableMotor READ enableMotor WRITE setEnableMotor NOTIFY enableMotorChanged)
    Q_PROPERTY(float maxMotorForce READ maxMotorForce WRITE setMaxMotorForce NOTIFY maxMotorForceChanged)
    Q_PROPERTY(float motorSpeed READ motorSpeed WRITE setMotorSpeed NOTIFY motorSpeedChanged)

public:
    explicit Box2DPrismaticJoint(QObject *parent = 0);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    QPointF localAxisA() const;
    void setLocalAxisA(const QPointF &localAxisA);

    float referenceAngle() const;
    void setReferenceAngle(float referenceAngle);

    bool enableLimit() const;
    void setEnableLimit(bool enableLimit);

    float lowerTranslation() const;
    void setLowerTranslation(float lowerTranslation);

    float upperTranslation() const;
    void setUpperTranslation(float upperTranslation);

    bool enableMotor() const;
    void setEnableMotor(bool enableMotor);

    float maxMotorForce() const;
    void setMaxMotorForce(float maxMotorForce);

    float motorSpeed() const;
    void setMotorSpeed(float motorSpeed);

    Q_INVOKABLE float getJointTranslation() const;
    Q_INVOKABLE float getJointSpeed() const;

    b2PrismaticJoint *prismaticJoint() const;

signals:
    void localAnchorAChanged();
    void localAnchorBChanged();
    void localAxisAChanged();
    void referenceAngleChanged();
    void enableLimitChanged();
    void lowerTranslationChanged();
    void upperTranslationChanged();
    void enableMotorChanged();
    void maxMotorForceChanged();
    void motorSpeedChanged();

protected:
    b2Joint *createJoint();

private:
    QPointF m_localAnchorA;
    QPointF m_localAnchorB;
    QPointF m_localAxisA;
    float m_referenceAngle;
    bool m_enableLimit;
    float m_lowerTranslation;
    float m_upperTranslation;
    bool m_enableMotor;
    float m_maxMotorForce;
    float m_motorSpeed;

    bool m_defaultLocalAnchorA;
    bool m_defaultLocalAnchorB;
    bool m_defaultReferenceAngle;
};

inline QPointF Box2DPrismaticJoint::localAnchorA() const
{
    return m_localAnchorA;
}

inline QPointF Box2DPrismaticJoint::localAnchorB() const
{
    return m_localAnchorB;
}

inline QPointF Box2DPrismaticJoint::localAxisA() const
{
    return m_localAxisA;
}

inline float Box2DPrismaticJoint::referenceAngle() const
{
    return m_referenceAngle;
}

inline bool Box2DPrismaticJoint::enableLimit() const
{
    return m_enableLimit;
}

inline float Box2DPrismaticJoint::lowerTranslation() const
{
    return m_lowerTranslation;
}

inline float Box2DPrismaticJoint::upperTranslation() const
{
    return m_upperTranslation;
}

inline bool Box2DPrismaticJoint::enableMotor() const
{
    return m_enableMotor;
}

inline float Box2DPrismaticJoint::maxMotorForce() const
{
    return m_maxMotorForce;
}

inline float Box2DPrismaticJoint::motorSpeed() const
{
    return m_motorSpeed;
}

inline b2PrismaticJoint *Box2DPrismaticJoint::prismaticJoint() const
{
    return static_cast<b2PrismaticJoint*>(joint());
}

#endif // BOX2DPRISMATICJOINT_H
