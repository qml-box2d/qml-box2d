import Box2D 2.0

Body {
    id: body

    property alias fixture: circle

    property alias density: circle.density
    property alias friction: circle.friction
    property alias restitution: circle.restitution
    property alias sensor: circle.sensor
    property alias categories: circle.categories
    property alias collidesWith: circle.collidesWith
    property alias groupIndex: circle.groupIndex

    property alias x: circle.x
    property alias y: circle.y
    property alias radius: circle.radius

    signal beginContact(Fixture other)
    signal endContact(Fixture other)

    Circle {
        id: circle

        onBeginContact: body.beginContact(other)
        onEndContact: body.endContact(other)
    }
}
