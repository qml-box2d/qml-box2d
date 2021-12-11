import QtQuick
import Box2D
import "../shared"

PhysicsItem {
    id: wall

    signal beginContact(Fixture other)

    fixtures: Box {
        width: wall.width
        height: wall.height
        friction: 1
        density: 1
        onBeginContact: wall.beginContact(other)
    }

    Image {
        source: "images/wall.jpg"
        fillMode: Image.Tile
        anchors.fill: parent
    }
}
