import Box2D 2.0

Body {
    id: body

    property alias fixture: box

    property alias density: box.density
    property alias friction: box.friction
    property alias restitution: box.restitution
    property alias sensor: box.sensor
    property alias categories: box.categories
    property alias collidesWith: box.collidesWith
    property alias groupIndex: box.groupIndex

    property alias x: box.x
    property alias y: box.y
    property alias width: box.width
    property alias height: box.height

    signal beginContact(Fixture other)
    signal endContact(Fixture other)

    Box {
        id: box

        onBeginContact: body.beginContact(other)
        onEndContact: body.endContact(other)
    }
}
