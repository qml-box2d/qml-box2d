/*
 * box2dcontact.cpp
 * Copyright (c) 2014 Moukhlynin Ruslan <ruslan@khvmntk.ru>
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

#include "box2dcontact.h"

#include "box2dworld.h"
#include "box2dfixture.h"


/*!
   \qmltype Contact
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
   \brief
*/


Box2DContact::Box2DContact(b2Contact *contact) :
    mContact(contact)
{
}

void Box2DContact::setContact(b2Contact *contact)
{
    mContact = contact;
}

/*!
 * \qmlmethod Contact::isTouching()
    returns true if two things are touching each other
 */
bool Box2DContact::isTouching()
{
    return mContact->IsTouching();
}

/*!
 \qmlproperty bool Contact::enabled
    DOCME
*/
bool Box2DContact::isEnabled() const
{
    return mContact->IsEnabled();
}

void Box2DContact::setEnabled(bool enabled)
{
    mContact->SetEnabled(enabled);
}

/*!
 \qmlproperty Fixture Contact::fixtureA

 */
Box2DFixture *Box2DContact::fixtureA() const
{
    b2Fixture *fixture = mContact->GetFixtureA();
    if(fixture)
        return toBox2DFixture(fixture);
    return NULL;
}

/*!
 \qmlproperty Fixture Contact::fixtureB

 */
Box2DFixture *Box2DContact::fixtureB() const
{
    b2Fixture *fixture = mContact->GetFixtureB();
    if(fixture)
        return toBox2DFixture(fixture);
    return NULL;
}

/*!
 \qmlproperty int Contact::childIndexA

 */
int Box2DContact::childIndexA() const
{
    return mContact->GetChildIndexA();
}
/*!
 \qmlproperty int Contact::childIndexB

 */
int Box2DContact::childIndexB() const
{
    return mContact->GetChildIndexB();
}

/*!
 \qmlproperty real Contact::fiction
 */
qreal Box2DContact::getFriction() const
{
    return mContact->GetFriction();
}

void Box2DContact::setFriction(qreal friction)
{
    mContact->SetFriction(friction);
}

/*!
\qmlmethod Contact::resetFriction()
 */
void Box2DContact::resetFriction()
{
    mContact->ResetFriction();
}

/*!
 \qmlproperty real Contact::restitution

 */
qreal Box2DContact::getRestitution() const
{
    return mContact->GetRestitution();
}

void Box2DContact::setRestitution(qreal restitution)
{
    mContact->SetRestitution(restitution);
}

/*!
\qmlmethod Contact::resetRestitution()
    method to reset the restitiution.
 */
void Box2DContact::resetRestitution()
{
    mContact->ResetRestitution();
}

/*!
\qmlproperty real Contact::tangentSpeed

 */
qreal Box2DContact::getTangentSpeed() const
{
    return mContact->GetTangentSpeed();
}

void Box2DContact::setTangentSpeed(qreal speed)
{
    mContact->SetTangentSpeed(speed);
}
