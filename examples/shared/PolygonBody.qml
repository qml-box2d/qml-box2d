import Box2D 2.0

Body {
    id: body

    property alias fixture: polygon

    property alias density: polygon.density
    property alias friction: polygon.friction
    property alias restitution: polygon.restitution
    property alias sensor: polygon.sensor
    property alias categories: polygon.categories
    property alias collidesWith: polygon.collidesWith
    property alias groupIndex: polygon.groupIndex

    property alias vertices: polygon.vertices

    signal beginContact(Fixture other)
    signal endContact(Fixture other)

    Polygon {
        id: polygon

        onBeginContact: body.beginContact(other)
        onEndContact: body.endContact(other)
    }
}
