import Box2D 2.0

Body {
    property alias fixture: polygon

    property alias density: polygon.density
    property alias friction: polygon.friction
    property alias restitution: polygon.restitution
    property alias sensor: polygon.sensor
    property alias categories: polygon.categories
    property alias collidesWith: polygon.collidesWith
    property alias groupIndex: polygon.groupIndex

    property alias vertices: polygon.vertices

    Polygon { id: polygon }
}
