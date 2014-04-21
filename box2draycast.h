/*
 * box2draycast.h
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

#ifndef BOX2DRAYCAST_H
#define BOX2DRAYCAST_H

#include <QObject>
#include <QQmlParserStatus>
#include <QPointF>
#include <QVariant>

#include <Box2D.h>

class Box2DFixture;
class Box2DWorld;

class Box2DRayCast : public QObject, public QQmlParserStatus, public b2RayCastCallback
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_ENUMS(CastResult Loops)

    Q_PROPERTY(QPointF point1 READ point1 WRITE setPoint1 NOTIFY point1Changed)
    Q_PROPERTY(QPointF point2 READ point2 WRITE setPoint2 NOTIFY point2Changed)
    Q_PROPERTY(bool repeat READ repeat WRITE setRepeat NOTIFY repeatChanged)
    Q_PROPERTY(CastResult result READ result WRITE setResult)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(Box2DWorld *world READ world WRITE setWorld NOTIFY worldChanged)

public:
    enum CastResult {
        Ignore = -1,
        Terminate = 0,
        Continue = 1,
        Clip = 2
    };

    Box2DRayCast(QObject *parent = 0);
    float32 ReportFixture (b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction);

    void classBegin();
    void componentComplete();

protected:
    QPointF point1() const;
    void setPoint1(const QPointF &point1);

    QPointF point2() const;
    void setPoint2(const QPointF &point2);

    bool repeat() const;
    void setRepeat(bool repeat);

    CastResult result() const;
    void setResult(CastResult result);

    bool running() const;
    void setRunning(bool running);

    Box2DWorld * world() const;
    void setWorld(Box2DWorld *world);

    void startLoop(bool start);

private:
    bool mComponentComplete;
    b2Vec2 mPoint1;
    b2Vec2 mPoint2;
    bool mRepeat;
    CastResult mResult;
    bool mRunning;
    Box2DWorld *mWorld;

private slots:
    void cast();

signals:
    void casted(Box2DFixture *fixture, const QPointF &point, const QPointF &normal, qreal fraction);
    void point1Changed();
    void point2Changed();
    void repeatChanged();
    void runningChanged();
    void worldChanged();
};

#endif // BOX2DRAYCAST_H
