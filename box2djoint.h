/*
 * box2djoint.h
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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

#ifndef BOX2DJOINT_H
#define BOX2DJOINT_H

#include <QObject>
#include <QPointF>
#include <QQmlParserStatus>

#include <Box2D.h>

class b2World;
class Box2DBody;
class Box2DWorld;

class Box2DJoint : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_ENUMS(JointType)
    Q_PROPERTY(JointType jointType READ jointType CONSTANT)
    Q_PROPERTY(bool collideConnected READ collideConnected WRITE setCollideConnected NOTIFY collideConnectedChanged)
    Q_PROPERTY(Box2DBody *bodyA READ bodyA WRITE setBodyA NOTIFY bodyAChanged)
    Q_PROPERTY(Box2DBody *bodyB READ bodyB WRITE setBodyB NOTIFY bodyBChanged)

public:
    enum JointType { // Matches b2JointType
        UnknownJoint,
        RevoluteJoint,
        PrismaticJoint,
        DistanceJoint,
        PulleyJoint,
        MouseJoint,
        GearJoint,
        WheelJoint,
        WeldJoint,
        FrictionJoint,
        RopeJoint,
        MotorJoint
    };

    Box2DJoint(JointType jointType, QObject *parent = 0);
    ~Box2DJoint();

    JointType jointType() const;

    bool collideConnected() const;
    void setCollideConnected(bool collideConnected);

    Box2DBody *bodyA() const;
    void setBodyA(Box2DBody *bodyA);

    Box2DBody *bodyB() const;
    void setBodyB(Box2DBody *bodyB);

    void initialize();

    void nullifyJoint();
    Box2DWorld *world() const;
    b2Joint *joint() const;

    // QQmlParserStatus interface
    void classBegin() {}
    void componentComplete();

protected:
    virtual b2Joint *createJoint() = 0;
    void initializeJointDef(b2JointDef &def);

private slots:
    void bodyACreated();
    void bodyBCreated();

signals:
    void collideConnectedChanged();
    void bodyAChanged();
    void bodyBChanged();
    void created();

private:
    JointType mJointType;
    bool mCollideConnected;
    bool mComponentComplete;
    bool mInitializePending;
    Box2DBody *mBodyA;
    Box2DBody *mBodyB;
    Box2DWorld *mWorld;
    b2Joint *mJoint;
};

inline Box2DJoint::JointType Box2DJoint::jointType() const
{
    return mJointType;
}

inline bool Box2DJoint::collideConnected() const
{
    return mCollideConnected;
}

inline Box2DBody *Box2DJoint::bodyA() const
{
    return mBodyA;
}

inline Box2DBody *Box2DJoint::bodyB() const
{
    return mBodyB;
}

inline void Box2DJoint::nullifyJoint()
{
    mJoint = 0;
}

inline Box2DWorld *Box2DJoint::world() const
{
    return mWorld;
}

inline b2Joint *Box2DJoint::joint() const
{
    return mJoint;
}


/**
 * Convenience function to get the Box2DJoint wrapping a b2Joint.
 */
inline Box2DJoint *toBox2DJoint(b2Joint *joint)
{
    return static_cast<Box2DJoint*>(joint->GetUserData());
}


#endif // BOX2DJOINT_H
