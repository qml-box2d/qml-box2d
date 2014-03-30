#include "box2draycast.h"

#include "box2dfixture.h"
#include "box2dworld.h"


Box2DRayCast::Box2DRayCast(QQuickItem *parent) :
    QQuickItem(parent),
    mWorld(NULL),
    mPoint1(0,0),
    mPoint2(0,0),
    mMaxFraction(1)
{
}

void Box2DRayCast::componentComplete()
{
    mWorld = dynamic_cast<Box2DWorld *>(parentItem());
    if(mWorld)
    {
        connect(mWorld,SIGNAL(stepped()),this,SLOT(stepped()));
    }
}

QPointF Box2DRayCast::point1() const
{
    return QPointF(mPoint1.x * scaleRatio, -mPoint1.y * scaleRatio);
}

void Box2DRayCast::setPoint1(QPointF point)
{
    if(point != point1())
    {
        mPoint1 =  b2Vec2(point.x() / scaleRatio, -point.y() / scaleRatio);
        emit point1Changed();
    }
}

QPointF Box2DRayCast::point2() const
{
    return QPointF(mPoint2.x * scaleRatio, -mPoint2.y * scaleRatio);
}

void Box2DRayCast::setPoint2(QPointF point)
{
    if(point != point2())
    {
        mPoint2 =  b2Vec2(point.x() / scaleRatio, -point.y() / scaleRatio);
        emit point2Changed();
    }
}

qreal Box2DRayCast::maxFraction() const
{
    return mMaxFraction;
}

void Box2DRayCast::setMaxFraction(qreal _maxFraction)
{
    if(mMaxFraction != _maxFraction)
    {
        mMaxFraction = _maxFraction;
        emit maxFractionChanged();
    }
}

void Box2DRayCast::stepped()
{
    b2RayCastOutput rayCastOutput;
    b2RayCastInput rayCastInput;
    rayCastInput.p1 = mPoint1;
    rayCastInput.p2 = mPoint2;
    rayCastInput.maxFraction = mMaxFraction;

    b2Body *body = mWorld->world()->GetBodyList();
    while(body != NULL)
    {
        b2Fixture *fixture = body->GetFixtureList();
        while(fixture != NULL)
        {
            if(fixture->RayCast(&rayCastOutput,rayCastInput,0))
            {
                QPoint normal(rayCastOutput.normal.x * scaleRatio, -rayCastOutput.normal.y * scaleRatio);
                emit casted(toBox2DFixture(fixture),normal,rayCastOutput.fraction);
            }
            fixture = fixture->GetNext();
        }
        body = body->GetNext();
    }
}
