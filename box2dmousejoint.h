/*
 * box2dmousejoint.h
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

#ifndef BOX2DMOUSEJOINT_H
#define BOX2DMOUSEJOINT_H

#include "box2djoint.h"
#include <box2d/box2d.h>

class Box2DMouseJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QPointF target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float maxForce READ maxForce WRITE setMaxForce NOTIFY maxForceChanged)
    Q_PROPERTY(float stiffness READ stiffness WRITE setStiffness NOTIFY stiffnessChanged)
    Q_PROPERTY(float damping READ damping WRITE setDamping NOTIFY dampingChanged)

public:
    explicit Box2DMouseJoint(QObject *parent = nullptr);

    float damping() const;
    void setDamping(float damping);

    float stiffness() const;
    void setStiffness(float stiffness);

    float maxForce() const;
    void setMaxForce(float maxForce);

    QPointF target() const;
    void setTarget(const QPointF &target);

    Q_INVOKABLE QPointF getReactionForce(float inv_dt) const;
    Q_INVOKABLE float getReactionTorque(float inv_dt) const;

    b2MouseJoint *mouseJoint() const;

signals:
    void targetChanged();
    void maxForceChanged();
    void stiffnessChanged();
    void dampingChanged();

protected:
    b2Joint *createJoint() override;

private:
    QPointF m_target;
    float m_maxForce;
    float m_stiffness;
    float m_damping;
};

inline float Box2DMouseJoint::damping() const
{
    return m_damping;
}

inline float Box2DMouseJoint::stiffness() const
{
    return m_stiffness;
}

inline float Box2DMouseJoint::maxForce() const
{
    return m_maxForce;
}

inline QPointF Box2DMouseJoint::target() const
{
    return m_target;
}

inline b2MouseJoint *Box2DMouseJoint::mouseJoint() const
{
    return static_cast<b2MouseJoint*>(joint());
}

#endif // BOX2DMOUSEJOINT_H
