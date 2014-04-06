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

#ifndef BOX2DWHEELJOINT_H
#define BOX2DWHEELJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class Box2DWheelJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)
    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float maxMotorTorque READ maxMotorTorque WRITE setMaxMotorTorque NOTIFY maxMotorTorqueChanged)
    Q_PROPERTY(float motorSpeed READ motorSpeed WRITE setMotorSpeed NOTIFY motorSpeedChanged)
    Q_PROPERTY(bool enableMotor READ enableMotor WRITE setEnableMotor NOTIFY enableMotorChanged)
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)
    Q_PROPERTY(QPointF localAxisA READ localAxisA WRITE setLocalAxisA NOTIFY localAxisAChanged)

public:
    explicit Box2DWheelJoint(QObject *parent = 0);

    float dampingRatio() const;
    void setDampingRatio(float dampingRatio);

    float frequencyHz() const;
    void setFrequencyHz(float frequencyHz);

    float maxMotorTorque() const;
    void setMaxMotorTorque(float maxMotorTorque);

    float motorSpeed() const;
    void setMotorSpeed(float motorSpeed);

    bool enableMotor() const;
    void setEnableMotor(bool enableMotor);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    QPointF localAxisA() const;
    void setLocalAxisA(const QPointF &localAxisA);

    b2WheelJoint *wheelJoint() const;

    Q_INVOKABLE QPointF getReactionForce(float32 inv_dt) const;
    Q_INVOKABLE float getReactionTorque(float32 inv_dt) const;
    Q_INVOKABLE float getJointTranslation() const;
    Q_INVOKABLE float getJointSpeed() const;

signals:
    void dampingRatioChanged();
    void frequencyHzChanged();
    void maxMotorTorqueChanged();
    void motorSpeedChanged();
    void enableMotorChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();
    void localAxisAChanged();

protected:
    b2Joint *createJoint();

private:
    b2WheelJointDef mWheelJointDef;
    bool mAnchorsAuto;
};

inline float Box2DWheelJoint::dampingRatio() const
{
    return mWheelJointDef.dampingRatio;
}

inline float Box2DWheelJoint::frequencyHz() const
{
    return mWheelJointDef.frequencyHz;
}

inline float Box2DWheelJoint::maxMotorTorque() const
{
    return mWheelJointDef.maxMotorTorque;
}

inline bool Box2DWheelJoint::enableMotor() const
{
    return mWheelJointDef.enableMotor;
}

inline b2WheelJoint *Box2DWheelJoint::wheelJoint() const
{
    return static_cast<b2WheelJoint*>(joint());
}

#endif // BOX2DWHEELJOINT_H
