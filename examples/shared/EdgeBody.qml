import Box2D 1.1

Body {
    property alias fixture: edge

    property alias density: edge.density
    property alias friction: edge.friction
    property alias restitution: edge.restitution
    property alias sensor: edge.sensor
    property alias categories: edge.categories
    property alias collidesWith: edge.collidesWith
    property alias groupIndex: edge.groupIndex

    property alias vertices: edge.vertices

    Edge { id: edge }
}
