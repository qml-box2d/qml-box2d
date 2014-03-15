
#include "box2dcontact.h"
#include "box2dworld.h"
#include "box2dfixture.h"


Box2DContact::Box2DContact(b2Contact * contact) :
    QObject(NULL),
    mContact(contact)
{
}

void Box2DContact::setContact(b2Contact *contact)
{
    mContact = contact;
}

bool Box2DContact::isTouching()
{
    return mContact->IsTouching();
}

bool Box2DContact::isEnabled()
{
    return mContact->IsEnabled();
}

void Box2DContact::setEnabled(bool enabled)
{
    mContact->SetEnabled(enabled);
}

Box2DFixture *Box2DContact::fixtureA()
{
    b2Fixture * fixture = mContact->GetFixtureA();
    if(fixture)
        return toBox2DFixture(fixture);
    return NULL;
}

Box2DFixture *Box2DContact::fixtureB()
{
    b2Fixture * fixture = mContact->GetFixtureB();
    if(fixture)
        return toBox2DFixture(fixture);
    return NULL;
}

int Box2DContact::childIndexA()
{
    return mContact->GetChildIndexA();
}

int Box2DContact::childIndexB()
{
    return mContact->GetChildIndexB();
}

qreal Box2DContact::getFriction()
{
    return mContact->GetFriction();
}

void Box2DContact::setFriction(qreal friction)
{
    mContact->SetFriction(friction);
}

void Box2DContact::resetFriction()
{
    mContact->ResetFriction();
}

qreal Box2DContact::getRestitution()
{
    return mContact->GetRestitution();
}

void Box2DContact::setRestitution(qreal restitution)
{
    mContact->SetRestitution(restitution);
}

void Box2DContact::resetRestitution()
{
    mContact->ResetRestitution();
}

qreal Box2DContact::getTangentSpeed()
{
    return mContact->GetTangentSpeed() * scaleRatio;
}

void Box2DContact::setTangentSpeed(qreal speed)
{
    mContact->SetTangentSpeed(speed / scaleRatio);
}
