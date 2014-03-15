#ifndef BOX2DCONTACT_H
#define BOX2DCONTACT_H

#include <QObject>
#include <Box2D.h>

class Box2DFixture;

class Box2DContact : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(Box2DFixture * fixtureA READ fixtureA)
    Q_PROPERTY(Box2DFixture * fixtureB READ fixtureB)
    Q_PROPERTY(int childIndexA READ childIndexA)
    Q_PROPERTY(int childIndexB READ childIndexB)
    Q_PROPERTY(qreal friction READ getFriction WRITE setFriction)
    Q_PROPERTY(qreal restitution READ getRestitution WRITE setRestitution)
    Q_PROPERTY(qreal tangentSpeed READ getTangentSpeed WRITE setTangentSpeed)

public:
    Box2DContact(b2Contact * contact = 0);
    void setContact(b2Contact * contact);
    Q_INVOKABLE bool isTouching();
    Q_INVOKABLE void resetFriction();
    Q_INVOKABLE void resetRestitution();

protected:
    b2Contact * mContact;

    bool isEnabled();
    void setEnabled(bool enabled);
    Box2DFixture * fixtureA();
    Box2DFixture * fixtureB();
    int childIndexA();
    int childIndexB();
    qreal getFriction();
    void setFriction(qreal friction);
    qreal getRestitution();
    void setRestitution(qreal restitution);
    qreal getTangentSpeed();
    void setTangentSpeed(qreal speed);
};

#endif // BOX2DCONTACT_H
