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

#ifndef BOX2WELDJOINT_H
#define BOX2WELDJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class Box2DWeldJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float referenceAngle READ referenceAngle WRITE setReferenceAngle NOTIFY referenceAngleChanged)
    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)

public:
    explicit Box2DWeldJoint(QObject *parent = 0);

    float referenceAngle() const;
    void setReferenceAngle(float referenceAngle);

    float frequencyHz() const;
    void setFrequencyHz(float frequencyHz);

    float dampingRatio() const;
    void setDampingRatio(float dampingRatio);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    b2WeldJoint *weldJoint() const;

signals:
    void referenceAngleChanged();
    void frequencyHzChanged();
    void dampingRatioChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();

protected:
    b2Joint *createJoint();

private:
    QPointF m_localAnchorA;
    QPointF m_localAnchorB;
    float m_referenceAngle;
    float m_frequencyHz;
    float m_dampingRatio;

    bool m_defaultLocalAnchorA;
    bool m_defaultLocalAnchorB;
    bool m_defaultReferenceAngle;
};

inline QPointF Box2DWeldJoint::localAnchorA() const
{
    return m_localAnchorA;
}

inline QPointF Box2DWeldJoint::localAnchorB() const
{
    return m_localAnchorB;
}

inline float Box2DWeldJoint::referenceAngle() const
{
    return m_referenceAngle;
}

inline float Box2DWeldJoint::frequencyHz() const
{
    return m_frequencyHz;
}

inline float Box2DWeldJoint::dampingRatio() const
{
    return m_dampingRatio;
}

inline b2WeldJoint *Box2DWeldJoint::weldJoint() const
{
    return static_cast<b2WeldJoint*>(joint());
}

#endif // BOX2WELDJOINT_H
