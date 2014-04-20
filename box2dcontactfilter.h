/*
 * box2dcontactfilter.h
 * Copyright (c) 2014 Ruslan Mouchlynin <ruslan@khvmntk.ru>
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

#ifndef BOX2DCONTACTFILTER_H
#define BOX2DCONTACTFILTER_H

#include <QObject>
#include <QQmlParserStatus>

#include <Box2D.h>

class Box2DWorld;
class Box2DFixture;

class Box2DContactFilter : public QObject, public b2ContactFilter, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool result READ result WRITE setResult)
    Q_PROPERTY(Box2DWorld *world READ world WRITE setWorld NOTIFY worldChanged)

public:
    Box2DContactFilter(QObject *parent = 0);
    bool ShouldCollide(b2Fixture *fixtureA, b2Fixture *fixtureB);

    void classBegin();
    void componentComplete();

protected:
    bool mEnabled;
    bool mResult;
    Box2DWorld *mWorld;

    bool isEnabled() const;
    void setEnabled(bool enabled);

    bool result() const;
    void setResult(bool result);

    Box2DWorld *world() const;
    void setWorld(Box2DWorld *world);

    void installContactFilter(bool install);

signals:
    void contacted(Box2DFixture *fixtureA,Box2DFixture *fixtureB);
    void enabledChanged();
    void worldChanged();
};

#endif // BOX2DCONTACTFILTER_H
