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

class b2World;
class b2PulleyJoint;
class b2PulleyJointDef;

class Box2DPulleyJoint : public Box2DJoint
{
    Q_OBJECT
    Q_PROPERTY(float lengthA READ lengthA WRITE setLengthA NOTIFY lengthAChanged)
    Q_PROPERTY(float lengthB READ lengthB WRITE setLengthB NOTIFY lengthBChanged)
    Q_PROPERTY(float ratio READ ratio WRITE setRatio NOTIFY ratioChanged)
    Q_PROPERTY(QPointF groundAnchorA READ groundAnchorA WRITE setGroundAnchorA NOTIFY groundAnchorAChanged)
    Q_PROPERTY(QPointF groundAnchorB READ groundAnchorB WRITE setGroundAnchorB NOTIFY groundAnchorBChanged)
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)

public:
    explicit Box2DPulleyJoint(QObject *parent = 0);
    ~Box2DPulleyJoint();

    float lengthA() const;
    void setLengthA(float lengthA);

    float lengthB() const;
    void setLengthB(float lengthB);

    float ratio() const;
    void setRatio(float ratio);

    QPointF groundAnchorA() const;
    void setGroundAnchorA(const QPointF &groundAnchorA);

    QPointF groundAnchorB() const;
    void setGroundAnchorB(const QPointF &groundAnchorB);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &localAnchorB);

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);
    b2Joint * GetJoint();

    Q_INVOKABLE float GetCurrentLengthA() const;
    Q_INVOKABLE float GetCurrentLengthB() const;
    Q_INVOKABLE QPointF GetReactionForce(float32 inv_dt) const;
    Q_INVOKABLE float GetReactionTorque(float32 inv_dt) const;

signals:
    void lengthAChanged();
    void lengthBChanged();
    void ratioChanged();
    void groundAnchorAChanged();
    void groundAnchorBChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();

private:
    b2PulleyJointDef mPulleyJointDef;
    b2PulleyJoint *mPulleyJoint;
};



#endif // BOX2PULLEYJOINT_H
