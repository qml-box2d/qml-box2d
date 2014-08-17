import QtQuick 2.0
import Box2D 1.1

Rectangle {
    id: wall
    color: "brown"

    property alias image: image.source

    Body {
        id: body

        world: physicsWorld
        target: wall
        bodyType: Body.Static

        fixtures: Box {
            width: wall.width
            height: wall.height
            friction: 1.0
        }
    }

    Image {
        id: image
        anchors.fill: parent
        source: "images/brickwall.png"
        fillMode: Image.Tile
    }
}
