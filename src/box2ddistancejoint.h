/*
 * box2ddistancejoint.h
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

#ifndef BOX2DDISTANCEJOINT_H
#define BOX2DDISTANCEJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class Box2DDistanceJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)
    Q_PROPERTY(float length READ length WRITE setLength NOTIFY lengthChanged)
    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)

public:
    explicit Box2DDistanceJoint(QObject *parent = 0);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    float length() const;
    void setLength(float length);

    float frequencyHz() const;
    void setFrequencyHz(float frequencyHz);

    float dampingRatio() const;
    void setDampingRatio(float dampingRatio);

    b2DistanceJoint *distanceJoint() const;

    Q_INVOKABLE QPointF getReactionForce(float32 inv_dt) const;
    Q_INVOKABLE float getReactionTorque(float32 inv_dt) const;

signals:
    void localAnchorAChanged();
    void localAnchorBChanged();
    void lengthChanged();
    void frequencyHzChanged();
    void dampingRatioChanged();

protected:
    b2Joint *createJoint();

private:
    QPointF m_localAnchorA;
    QPointF m_localAnchorB;
    float m_length;
    float m_frequencyHz;
    float m_dampingRatio;
    bool m_defaultLocalAnchorA;
    bool m_defaultLocalAnchorB;
    bool m_defaultLength;
};

inline QPointF Box2DDistanceJoint::localAnchorA() const
{
    return m_localAnchorA;
}

inline QPointF Box2DDistanceJoint::localAnchorB() const
{
    return m_localAnchorB;
}

inline float Box2DDistanceJoint::length() const
{
    return m_length;
}

inline float Box2DDistanceJoint::frequencyHz() const
{
    return m_frequencyHz;
}

inline float Box2DDistanceJoint::dampingRatio() const
{
    return m_dampingRatio;
}

inline b2DistanceJoint *Box2DDistanceJoint::distanceJoint() const
{
    return static_cast<b2DistanceJoint*>(joint());
}

#endif // BOX2DDISTANCEJOINT_H
