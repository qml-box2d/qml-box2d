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

#ifndef BOX2PULLEYJOINT_H
#define BOX2PULLEYJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class Box2DPulleyJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QVector2D groundAnchorA READ groundAnchorA WRITE setGroundAnchorA NOTIFY groundAnchorAChanged)
    Q_PROPERTY(QVector2D groundAnchorB READ groundAnchorB WRITE setGroundAnchorB NOTIFY groundAnchorBChanged)
    Q_PROPERTY(QVector2D localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QVector2D localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)
    Q_PROPERTY(float lengthA READ lengthA WRITE setLengthA NOTIFY lengthAChanged)
    Q_PROPERTY(float lengthB READ lengthB WRITE setLengthB NOTIFY lengthBChanged)
    Q_PROPERTY(float ratio READ ratio WRITE setRatio NOTIFY ratioChanged)

public:
    explicit Box2DPulleyJoint(QObject *parent = 0);

    QVector2D groundAnchorA() const;
    void setGroundAnchorA(const QVector2D &groundAnchorA);

    QVector2D groundAnchorB() const;
    void setGroundAnchorB(const QVector2D &groundAnchorB);

    QVector2D localAnchorA() const;
    void setLocalAnchorA(const QVector2D &localAnchorA);

    QVector2D localAnchorB() const;
    void setLocalAnchorB(const QVector2D &localAnchorB);

    float lengthA() const;
    void setLengthA(float lengthA);

    float lengthB() const;
    void setLengthB(float lengthB);

    float ratio() const;
    void setRatio(float ratio);

    b2PulleyJoint *pulleyJoint() const;

    Q_INVOKABLE float getCurrentLengthA() const;
    Q_INVOKABLE float getCurrentLengthB() const;
    Q_INVOKABLE QVector2D getReactionForce(float32 inv_dt) const;
    Q_INVOKABLE float getReactionTorque(float32 inv_dt) const;

signals:
    void groundAnchorAChanged();
    void groundAnchorBChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();
    void lengthAChanged();
    void lengthBChanged();
    void ratioChanged();

protected:
    b2Joint *createJoint();

private:
    QVector2D m_groundAnchorA;
    QVector2D m_groundAnchorB;
    QVector2D m_localAnchorA;
    QVector2D m_localAnchorB;
    float m_lengthA;
    float m_lengthB;
    float m_ratio;

    bool m_defaultLocalAnchorA;
    bool m_defaultLocalAnchorB;
    bool m_defaultLengthA;
    bool m_defaultLengthB;
};

inline QVector2D Box2DPulleyJoint::groundAnchorA() const
{
    return m_groundAnchorA;
}

inline QVector2D Box2DPulleyJoint::groundAnchorB() const
{
    return m_groundAnchorB;
}

inline QVector2D Box2DPulleyJoint::localAnchorA() const
{
    return m_localAnchorA;
}

inline QVector2D Box2DPulleyJoint::localAnchorB() const
{
    return m_localAnchorB;
}

inline float Box2DPulleyJoint::lengthA() const
{
    return m_lengthA;
}

inline float Box2DPulleyJoint::lengthB() const
{
    return m_lengthB;
}

inline float Box2DPulleyJoint::ratio() const
{
    return m_ratio;
}

inline b2PulleyJoint *Box2DPulleyJoint::pulleyJoint() const
{
    return static_cast<b2PulleyJoint*>(joint());
}

#endif // BOX2PULLEYJOINT_H
