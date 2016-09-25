/*
 * box2dgearjoint.h
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

#ifndef BOX2DGEARJOINT_H
#define BOX2DGEARJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class Box2DGearJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(Box2DJoint *joint1 READ joint1 WRITE setJoint1 NOTIFY joint1Changed)
    Q_PROPERTY(Box2DJoint *joint2 READ joint2 WRITE setJoint2 NOTIFY joint2Changed)
    Q_PROPERTY(float ratio READ ratio WRITE setRatio NOTIFY ratioChanged)

public:
    explicit Box2DGearJoint(QObject *parent = 0);

    Box2DJoint *joint1() const;
    void setJoint1(Box2DJoint *joint1);

    Box2DJoint *joint2() const;
    void setJoint2(Box2DJoint *joint2);

    float ratio() const;
    void setRatio(float ratio);

    b2GearJoint *gearJoint() const;

signals:
    void joint1Changed();
    void joint2Changed();
    void ratioChanged();

protected:
    b2Joint *createJoint();

private slots:
    void joint1Created();
    void joint2Created();

private:
    Box2DJoint *m_joint1;
    Box2DJoint *m_joint2;
    float m_ratio;
};

inline Box2DJoint *Box2DGearJoint::joint1() const
{
    return m_joint1;
}

inline Box2DJoint *Box2DGearJoint::joint2() const
{
    return m_joint2;
}

inline float Box2DGearJoint::ratio() const
{
    return m_ratio;
}

inline b2GearJoint *Box2DGearJoint::gearJoint() const
{
    return static_cast<b2GearJoint*>(joint());
}

#endif // BOX2DGEARJOINT_H
