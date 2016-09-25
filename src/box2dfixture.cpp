/*
 * box2dfixture.cpp
 * Copyright (c) 2010-2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2011 Daker Fernandes Pinheiro <daker.pinheiro@openbossa.org>
 * Copyright (c) 2011 Alessandro Portale <alessandro.portale@nokia.com>
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

#include "box2dfixture.h"

#include "box2dbody.h"
#include "box2dworld.h"

#include <QDebug>

#include "Common/b2Math.h"

/*!
   \qmltype Fixture
   \inqmlmodule Box2d 1.0
   \ingroup Box2d
   \inherits QObject
    \brief This element is uncreatable to connect to this element use a Box , Circle , Edge, Polygon

Recall that shapes don’t know about {Body}{bodies} and may be used independently
of the physics simulation.
Therefore Box2D provides the Fixture  to attach shapes to {Body}{bodies}. A Body may have
zero or more {Body::fixtures}  {fixtures}.
A body with multiple fixtures is sometimes called a compound body.

Fixtures hold the following:
\list
\li  a single shape
\li  broad-phase proxies
\li density, friction, and restitution
\li collision filtering flags
\li back pointer to the parent body
\li user data
\li sensor flag
\endlist

These are described in the following sections.
\section1 Fixture Creation
Fixtures are created by initializing a fixture definition and then passing the definition to the
parent Body.

\code
    add example
\endcode

This creates the fixture and attaches it to the Body. You can create multiple
fixtures on a single body. You can destroy a fixture on the parent Body.
You may do this to model a breakable object. Otherwise you can just leave the fixture alone
and let the body destruction take care of destroying the attached

\code
    add destory example
    ixtures. myBody->DestroyFixture(myFixture);
\endcode

\section1 Filtering
#FIXME
Collision filtering allows you to prevent collision between fixtures. For example, say you make a
character that rides a bicycle. You want the bicycle to collide with the terrain and the character to
collide with the terrain, but you don't want the character to collide with the bicycle (because they must
overlap). Box2D supports such collision filtering using categories and groups.
Box2D supports 16 collision categories. For each fixture you can specify which category it belongs to.
You also specify what other categories this fixture can collide with. For example, you could specify in a
multiplayer game that all players don't collide with each other and monsters don't collide with each
other, but players and monsters should collide. This is done with masking bits. For example:
playerFixtureDef.filter.categoryBits = 0x0002;
monsterFixtureDef.filter.categoryBits = 0x0004;
playerFixtureDef.filter.maskBits = 0x0004;
monsterFixtureDef.filter.maskBits = 0x0002;
Here is the rule for a collision to occur:
uint16 catA = fixtureA.filter.categoryBits;
uint16 maskA = fixtureA.filter.maskBits;
uint16 catB = fixtureB.filter.categoryBits;
uint16 maskB = fixtureB.filter.maskBits;
if ((catA & maskB) != 0 && (catB & maskA) != 0)
{
 // fixtures can collide
}
Collision groups let you specify an integral group index. You can have all fixtures with the same group
index always collide (positive index) or never collide (negative index). Group indices are usually used for
things that are somehow related, like the parts of a bicycle. In the following example, fixture1 and
fixture2 always collide, but fixture3 and fixture4 never collide.
fixture1Def.filter.groupIndex = 2;
fixture2Def.filter.groupIndex = 2;
fixture3Def.filter.groupIndex = -8;
fixture4Def.filter.groupIndex = -8;
Collisions between fixtures of different group indices are filtered according the category and mask bits.
In other words, group filtering has higher precedence than category filtering.
Note that additional collision filtering occurs in Box2D. Here is a list:  A fixture on a static body can only collide with a dynamic body.
 A fixture on a kinematic body can only collide with a dynamic body.
 Fixtures on the same body never collide with each other.
 You can optionally enable/disable collision between fixtures on bodies connected by a joint.
Sometimes you might need to change collision filtering after a fixture has already been created. You can
get and set the b2Filter structure on an existing fixture using b2Fixture::GetFilterData and
b2Fixture::SetFilterData. Note that changing the filter data will not add or remove contacts until the next
time step (see the World class).


see {filtering}{Filtering Example}

*/


////////////////////////////////


/*!
 \qmlproperty float Fixture::density
The fixture density is used to compute the mass properties of the parent body. The density can be zero
or positive. You should generally use similar densities for all your fixtures. This will improve stacking
stability.

The mass of a body is not adjusted when you set the density. You must call ResetMassData for this to
occur.
    \code
        density: 5.0;
    \endcode
*/





/*!
\qmlproperty float Fixture::friction
friction is used to make objects slide along each other realistically. Box2D supports
    \list
        \li Body.Static
        \li Body.Dynamic
    \endlist

Friction uses the same parameter for both. Friction is simulated accurately in Box2D and
 the friction strength is proportional to the normal force (this is called Coulomb friction).
The friction parameter is usually set between 0 and 1, but can be any non-negative value.

A friction value of 0 turns off friction and a value of 1 makes the friction strong.
When the friction force is computed between two shapes, Box2D must combine the friction
parameters of the two parent fixtures. This is done with the geometric mean:
    \code
        float32 friction;
        friction = sqrtf(fixtureA->friction * fixtureB->friction);
    \endcode

So if one fixture has zero friction then the contact will have zero friction.

*/







/*!
\qmlproperty float Fixture::restitution
    Restitution is used to make objects bounce. The restitution value is usually set to be
between 0.0 and 1.0

Consider dropping a ball on a table. A value of zero means the ball won't bounce.
This is called an inelastic collision. A value of one means the ball's velocity will be exactly
reflected. This is called a perfectly elastic collision.

*/




/*!
/qmlproperty int Fixture::groupIndex
DOCME
*/


Box2DFixture::Box2DFixture(QObject *parent) :
    QObject(parent),
    mFixture(0),
    mBody(0)
{
    mFixtureDef.userData = this;
}

float Box2DFixture::density() const
{
    return mFixtureDef.density;
}

void Box2DFixture::setDensity(float density)
{
    if (mFixtureDef.density == density)
        return;

    mFixtureDef.density = density;
    if (mFixture)
        mFixture->SetDensity(density);
    emit densityChanged();
}

float Box2DFixture::friction() const
{
    return mFixtureDef.friction;
}

void Box2DFixture::setFriction(float friction)
{
    if (mFixtureDef.friction == friction)
        return;

    mFixtureDef.friction = friction;
    if (mFixture)
        mFixture->SetFriction(friction);
    emit frictionChanged();
}

float Box2DFixture::restitution() const
{
    return mFixtureDef.restitution;
}

void Box2DFixture::setRestitution(float restitution)
{
    if (mFixtureDef.restitution == restitution)
        return;

    mFixtureDef.restitution = restitution;
    if (mFixture)
        mFixture->SetRestitution(restitution);
    emit restitutionChanged();
}

bool Box2DFixture::isSensor() const
{
    return mFixtureDef.isSensor;
}

void Box2DFixture::setSensor(bool sensor)
{
    if (mFixtureDef.isSensor == sensor)
        return;

    mFixtureDef.isSensor = sensor;
    if (mFixture)
        mFixture->SetSensor(sensor);
    emit sensorChanged();
}

Box2DFixture::CategoryFlags Box2DFixture::categories() const
{
    return CategoryFlags(mFixtureDef.filter.categoryBits);
}

void Box2DFixture::setCategories(CategoryFlags layers)
{
    if (mFixtureDef.filter.categoryBits == layers)
        return;

    mFixtureDef.filter.categoryBits = layers;
    if (mFixture)
        mFixture->SetFilterData(mFixtureDef.filter);

    emit categoriesChanged();
}

Box2DFixture::CategoryFlags Box2DFixture::collidesWith() const
{
    return CategoryFlags(mFixtureDef.filter.maskBits);
}

void Box2DFixture::setCollidesWith(CategoryFlags layers)
{
    if (mFixtureDef.filter.maskBits == layers)
        return;

    mFixtureDef.filter.maskBits = layers;
    if (mFixture)
        mFixture->SetFilterData(mFixtureDef.filter);

    emit collidesWithChanged();
}

int Box2DFixture::groupIndex() const
{
    return mFixtureDef.filter.groupIndex;
}

void Box2DFixture::setGroupIndex(int groupIndex)
{
    if (mFixtureDef.filter.groupIndex == groupIndex)
        return;

    mFixtureDef.filter.groupIndex = groupIndex;
    if (mFixture)
        mFixture->SetFilterData(mFixtureDef.filter);

    emit groupIndexChanged();
}

void Box2DFixture::initialize(Box2DBody *body)
{
    mBody = body;
    b2Shape *shape = createShape();
    if (!shape)
        return;

    mFixtureDef.shape = shape;
    mFixture = body->body()->CreateFixture(&mFixtureDef);
    delete shape;
}

void Box2DFixture::recreateFixture()
{
    if (!mBody)
        return;
    if (mFixture)
        mBody->body()->DestroyFixture(mFixture);
    initialize(mBody);
}

/*!
 \qmlmethod Fixture::getBody()
 Target a body for the fictors

 */
Box2DBody *Box2DFixture::getBody() const
{
    return mBody;
}

//=================== BOX =======================

/*!
    \qmltype Box
    \ingroup Box2D
    \inherits Fixture
    \brief Provids a Box to hang off of a Body::fixture

    A Box is often used of a Body::fixture. Say that one would like to create a wall that other things can collide with.
One can acive this by making a Qml file called Wall.qml.
    \b{ Wall.qml }
    \code
        import QtQuick 2.0
        import Box2D 1.1
        Body {
            bodyType: Body.Static
            fixtures: Box { anchors.fill: parent }
        }
    \endcode

    another example would be the
    \l {boxes} {boxes example}
*/
void Box2DBox::setX(qreal x)
{
    if (mPosition.x() == x)
        return;
    mPosition.setX(x);
    recreateFixture();
    emit xChanged();
}

void Box2DBox::setY(qreal y)
{
    if (mPosition.y() == y)
        return;
    mPosition.setY(y);
    recreateFixture();
    emit yChanged();
}

void Box2DBox::setWidth(qreal width)
{
    if (mSize.width() == width)
        return;
    mSize.setWidth(width);
    recreateFixture();
    emit widthChanged();
}

void Box2DBox::setHeight(qreal height)
{
    if (mSize.height() == height)
        return;
    mSize.setHeight(height);
    recreateFixture();
    emit heightChanged();
}

void Box2DBox::setRotation(qreal rotation)
{
    if (mRotation == rotation)
        return;
    mRotation = rotation;
    recreateFixture();
    emit rotationChanged();
}

b2Shape *Box2DBox::createShape()
{
    const qreal halfWidth = width() * 0.5;
    const qreal halfHeight = height() * 0.5;
    const QPointF center(x() + halfWidth,
                         y() + halfHeight);

    b2PolygonShape *shape = new b2PolygonShape;
    shape->SetAsBox(b2Max(mBody->world()->toMeters(halfWidth), b2_linearSlop),
                    b2Max(mBody->world()->toMeters(halfHeight), b2_linearSlop),
                    mBody->world()->toMeters(center),
                    toRadians(rotation()));

    return shape;
}

//=================== CIRCLE =======================



/*!
    \qmltype Circle
    \ingroup Box2D
    \inherits Fixture
    \brief Circle Shapes
    Circle shapes have a position and radius. Circles are solid. You cannot make a hollow circle
    using the
\code
        Body{
        fixture{
        Circle{
            radius: 180;
            ...
            .......
            ............
        }
\endcode
*/

/*!
\qmlproperty int Circle::radius
    The over all radius of the Circle that is attached to the Fixture
     See also Rectangle::radius
*/



void Box2DCircle::setX(qreal x)
{
    if (mPosition.x() == x)
        return;
    mPosition.setX(x);
    recreateFixture();
    emit xChanged();
}

void Box2DCircle::setY(qreal y)
{
    if (mPosition.y() == y)
        return;
    mPosition.setY(y);
    recreateFixture();
    emit yChanged();
}

void Box2DCircle::setRadius(float radius)
{
    if (mRadius == radius)
        return;
    mRadius = radius;
    recreateFixture();
    emit radiusChanged();
}

b2Shape *Box2DCircle::createShape()
{
    b2CircleShape *shape = new b2CircleShape;

    shape->m_radius = mBody->world()->toMeters(radius());
    shape->m_p = mBody->world()->toMeters(position() + QPointF(radius(), radius()));

    return shape;
}

//=================== POLYGON =======================


/*!
    \qmltype Polygon
    \ingroup Box2D
    \inherits Fixture
    \brief Polygon shapes are solid convex polygons.
        A polygon is convex when all line segments connecting two points in the interior do
not cross any edge of the polygon. Polygons are solid and never hollow. A polygon must have
 3 or more vertices

*/
void Box2DPolygon::setVertices(const QVariantList &vertices)
{
    if (vertices == mVertices)
        return;

    mVertices = vertices;
    recreateFixture();
    emit verticesChanged();
}

b2Shape *Box2DPolygon::createShape()
{
    const int count = mVertices.length();
    if (count < 2 || count > b2_maxPolygonVertices) {
        qWarning() << "Polygon: Invalid number of vertices:" << count;
        return 0;
    }

    QScopedArrayPointer<b2Vec2> vertices(new b2Vec2[count]);

    for (int i = 0; i < count; ++i) {
        vertices[i] = mBody->world()->toMeters(mVertices.at(i).toPointF());

        if (i > 0) {
            if (b2DistanceSquared(vertices[i - 1], vertices[i]) <= b2_linearSlop * b2_linearSlop) {
                qWarning() << "Polygon: vertices are too close together";
                return 0;
            }
        }
    }

    b2PolygonShape *shape = new b2PolygonShape;
    shape->Set(vertices.data(), count);

    return shape;
}

//=================== CHAIN =======================

/*!
    \qmltype Chain
    \ingroup Box2D
    \inherits Fixture
    \brief The chain shape provides an efficient way to connect many edges together
to construct your static game worlds. Chain shapes automatically eliminate ghost collisions
 and provide two-sided collision.



*/

/*!
\qmlproperty bool Chain::loop
    DOCME
*/
/*!
\qmlproperty QPointF Chain::prevVertex
    DOCME
*/
/*!
\qmlproperty QPointF Chain::nextVertex
    DOCME
*/


*/


Box2DChain::Box2DChain(QQuickItem *parent) :
    Box2DFixture(parent),
    mLoop(false),
    mPrevVertexFlag(false),
    mNextVertexFlag(false)
{
}

void Box2DChain::setVertices(const QVariantList &vertices)
{
    if (vertices == mVertices)
        return;

    mVertices = vertices;
    recreateFixture();
    emit verticesChanged();
}

void Box2DChain::setLoop(bool loop)
{
    if (mLoop == loop)
        return;

    mLoop = loop;
    recreateFixture();
    emit loopChanged();
}

void Box2DChain::setPrevVertex(const QPointF &prevVertex)
{
    if (mPrevVertexFlag && mPrevVertex == prevVertex)
        return;

    mPrevVertex = prevVertex;
    mPrevVertexFlag = true;
    recreateFixture();
    emit prevVertexChanged();
}

void Box2DChain::setNextVertex(const QPointF &nextVertex)
{
    if (mNextVertexFlag && mNextVertex == nextVertex)
        return;

    mNextVertex = nextVertex;
    mNextVertexFlag = true;
    recreateFixture();
    emit nextVertexChanged();
}

b2Shape *Box2DChain::createShape()
{
    const int count = mVertices.length();

    if (count < 2 || (mLoop && count < 3)) {
        qWarning() << "Chain: Invalid number of vertices:" << count;
        return 0;
    }

    QScopedArrayPointer<b2Vec2> vertices(new b2Vec2[count]);

    for (int i = 0; i < count; ++i) {
        vertices[i] = mBody->world()->toMeters(mVertices.at(i).toPointF());

        if (i > 0) {
            if (b2DistanceSquared(vertices[i - 1], vertices[i]) <= b2_linearSlop * b2_linearSlop) {
                qWarning() << "Chain: vertices are too close together";
                return 0;
            }
        }
    }

    b2ChainShape *shape = new b2ChainShape;
    if (mLoop) {
        shape->CreateLoop(vertices.data(), count);
    } else {
        shape->CreateChain(vertices.data(), count);

        if (mPrevVertexFlag)
            shape->SetPrevVertex(mBody->world()->toMeters(mPrevVertex));
        if (mNextVertexFlag)
            shape->SetNextVertex(mBody->world()->toMeters(mNextVertex));
    }

    return shape;
}

//=================== EDGE =======================


/*!
    \qmltype Edge
    \inqmlmodule Box2D 1.1
    \inherits Fixture
    \brief Edge shapes are line segments.

These are provided to assist in making a free-form static environment for your game.
A major limitation of edge shapes is that they can collide with circles and polygons but
not with themselves. The collision algorithms used by Box2D require that at least one
of two colliding shapes have volume. Edge shapes have no volume, so edge-edge collision is not possible.


In many cases a game environment is constructed by connecting several Edge shapes
end-to-end. This can give rise to an unexpected artifact when a Polygon slides along the Chain
of Edges. In the figure below we see a Box colliding with an internal vertex. These ghost
collisions are caused when the Polygon collides with an internal vertex generating an
internal collision normal.

\b{Note} In general stitching edges together this way is a bit wasteful and tedious. You might just
want to use a Chain.

\sa Chain
*/


void Box2DEdge::setVertices(const QVariantList &vertices)
{
    if (vertices == mVertices)
        return;

    mVertices = vertices;
    recreateFixture();
    emit verticesChanged();
}

b2Shape *Box2DEdge::createShape()
{
    const int count = mVertices.length();
    if (count != 2) {
        qWarning() << "Edge: Invalid number of vertices:" << count;
        return 0;
    }
    const b2Vec2 vertex1 = mBody->world()->toMeters(mVertices.at(0).toPointF());
    const b2Vec2 vertex2 = mBody->world()->toMeters(mVertices.at(1).toPointF());
    if (b2DistanceSquared(vertex1, vertex2) <= b2_linearSlop * b2_linearSlop) {
        qWarning() << "Edge: vertices are too close together";
        return 0;
    }
    b2EdgeShape *shape = new b2EdgeShape;
    shape->Set(vertex1, vertex2);

    return shape;
}
