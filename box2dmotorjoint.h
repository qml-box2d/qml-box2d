/*
 * box2dmotorjoint.h
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

#ifndef BOX2DMOTORJOINT_H
#define BOX2DMOTORJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class Box2DMotorJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QPointF linearOffset READ linearOffset WRITE setLinearOffset NOTIFY linearOffsetChanged)
    Q_PROPERTY(float angularOffset READ angularOffset WRITE setAngularOffset NOTIFY angularOffsetChanged)
    Q_PROPERTY(float maxForce READ maxForce WRITE setMaxForce NOTIFY maxForceChanged)
    Q_PROPERTY(float maxTorque READ maxTorque WRITE setMaxTorque NOTIFY maxTorqueChanged)
    Q_PROPERTY(float correctionFactor READ correctionFactor WRITE setCorrectionFactor NOTIFY correctionFactorChanged)

public:
    explicit Box2DMotorJoint(QObject *parent = 0);

    QPointF linearOffset() const;
    void setLinearOffset(const QPointF & linearOffset);

    float angularOffset() const;
    void setAngularOffset(float angularOffset);

    float maxForce() const;
    void setMaxForce(float maxForce);

    float maxTorque() const;
    void setMaxTorque(float maxTorque);

    float correctionFactor() const;
    void setCorrectionFactor(float correctionFactor);

    b2MotorJoint *motorJoint() const;

signals:
    void linearOffsetChanged();
    void angularOffsetChanged();
    void maxForceChanged();
    void maxTorqueChanged();
    void correctionFactorChanged();

protected:
    b2Joint *createJoint();

private:
    QPointF m_linearOffset;
    float m_angularOffset;
    float m_maxForce;
    float m_maxTorque;
    float m_correctionFactor;
    bool m_defaultLinearOffset;
    bool m_defaultAngularOffset;
};

inline QPointF Box2DMotorJoint::linearOffset() const
{
    return m_linearOffset;
}

inline float Box2DMotorJoint::angularOffset() const
{
    return m_angularOffset;
}

inline float Box2DMotorJoint::maxForce() const
{
    return m_maxForce;
}

inline float Box2DMotorJoint::maxTorque() const
{
    return m_maxTorque;
}

inline float Box2DMotorJoint::correctionFactor() const
{
    return m_correctionFactor;
}

inline b2MotorJoint *Box2DMotorJoint::motorJoint() const
{
    return static_cast<b2MotorJoint*>(joint());
}

#endif // BOX2DMOTORJOINT_H
