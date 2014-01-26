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

class b2World;
class b2GearJoint;
class b2GearJointDef;

class Box2DGearJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(Box2DJoint * joint1 READ joint1 WRITE setJoint1 NOTIFY joint1Changed)
    Q_PROPERTY(Box2DJoint * joint2 READ joint2 WRITE setJoint2 NOTIFY joint2Changed)
    Q_PROPERTY(float ratio READ ratio WRITE setRatio NOTIFY ratioChanged)

public:
    explicit Box2DGearJoint(QObject *parent = 0);
    ~Box2DGearJoint();

    float ratio() const;
    void setRatio(float _ratio);

    Box2DJoint *joint1() const;
    void setJoint1(Box2DJoint *_joint1);

    Box2DJoint *joint2() const;
    void setJoint2(Box2DJoint *_joint2);

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);
    b2Joint * GetJoint();

signals:
    void ratioChanged();
    void joint1Changed();
    void joint2Changed();

private slots:
    void joint1Created();
    void joint2Created();

private:
    b2GearJointDef mGearJointDef;
    b2GearJoint *mGearJoint;
};



#endif // BOX2DGEARJOINT_H
