/*
 * box2dropejoint.h
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

#ifndef BOX2DROPEJOINT_H
#define BOX2DROPEJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2RopeJoint;

class Box2DRopeJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)
    Q_PROPERTY(float maxLength READ maxLength WRITE setMaxLength NOTIFY maxLengthChanged)

public:
    explicit Box2DRopeJoint(QObject *parent = 0);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    float maxLength() const;
    void setMaxLength(float maxLength);

    b2RopeJoint *ropeJoint() const;

    Q_INVOKABLE QPointF getReactionForce(float32 inv_dt) const;
    Q_INVOKABLE float getReactionTorque(float32 inv_dt) const;

signals:
    void localAnchorAChanged();
    void localAnchorBChanged();
    void maxLengthChanged();

protected:
    b2Joint *createJoint();

private:
    QPointF m_localAnchorA;
    QPointF m_localAnchorB;
    float m_maxLength;

    bool m_defaultLocalAnchorA;
    bool m_defaultLocalAnchorB;
};

inline QPointF Box2DRopeJoint::localAnchorA() const
{
    return m_localAnchorA;
}

inline QPointF Box2DRopeJoint::localAnchorB() const
{
    return m_localAnchorB;
}

inline float Box2DRopeJoint::maxLength() const
{
    return m_maxLength;
}

inline b2RopeJoint *Box2DRopeJoint::ropeJoint() const
{
    return static_cast<b2RopeJoint*>(joint());
}

#endif // BOX2DROPEJOINT_H
