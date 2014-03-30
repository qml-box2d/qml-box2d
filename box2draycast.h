#ifndef BOX2DRAYCAST_H
#define BOX2DRAYCAST_H

#include <QQuickItem>
#include <Box2D.h>

class Box2DWorld;
class Box2DFixture;

class Box2DRayCast : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF point1 READ point1 WRITE setPoint1 NOTIFY point1Changed)
    Q_PROPERTY(QPointF point2 READ point2 WRITE setPoint2 NOTIFY point2Changed)
    Q_PROPERTY(qreal maxFraction READ maxFraction WRITE setMaxFraction NOTIFY maxFractionChanged)

public:
    explicit Box2DRayCast(QQuickItem *parent = 0);
    void componentComplete();

protected:
    Box2DWorld * mWorld;
    b2Vec2 mPoint1;
    b2Vec2 mPoint2;
    qreal mMaxFraction;

    QPointF point1() const;
    void setPoint1(QPointF point);

    QPointF point2() const;
    void setPoint2(QPointF point);

    qreal maxFraction() const;
    void setMaxFraction(qreal _maxFraction);

protected slots:
    void stepped();

signals:
    void point1Changed();
    void point2Changed();
    void maxFractionChanged();
    void casted(Box2DFixture * fixture,QPointF normal,qreal fraction);
};

#endif // BOX2DRAYCAST_H
