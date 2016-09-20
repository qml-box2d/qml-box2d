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
#include <QPointF>

#include <Box2D.h>

class Box2DFixture;

class Box2DRayCast : public QObject, public b2RayCastCallback
{
    Q_OBJECT

    Q_PROPERTY(float maxFraction READ maxFraction WRITE setMaxFraction)

public:
    Box2DRayCast(QObject *parent = 0);

    float32 ReportFixture(b2Fixture *fixture,
                          const b2Vec2 &point,
                          const b2Vec2 &normal,
                          float32 fraction);

    float maxFraction() const;
    void setMaxFraction(float maxFraction);

signals:
    void fixtureReported(Box2DFixture *fixture,
                         const QPointF &point,
                         const QPointF &normal,
                         qreal fraction);

private:
    float mMaxFraction;
};

inline float Box2DRayCast::maxFraction() const
{
    return mMaxFraction;
}

inline void Box2DRayCast::setMaxFraction(float maxFraction)
{
    mMaxFraction = maxFraction;
}

#endif // BOX2DRAYCAST_H
