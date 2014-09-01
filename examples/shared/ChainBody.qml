import Box2D 2.0

Body {
    property alias fixture: chain

    property alias density: chain.density
    property alias friction: chain.friction
    property alias restitution: chain.restitution
    property alias sensor: chain.sensor
    property alias categories: chain.categories
    property alias collidesWith: chain.collidesWith
    property alias groupIndex: chain.groupIndex

    property alias vertices: chain.vertices
    property alias loop: chain.loop
    property alias prevVertex: chain.prevVertex
    property alias nextVertex: chain.nextVertex

    Chain { id: chain }
}
