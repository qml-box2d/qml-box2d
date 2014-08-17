import QtQuick 2.0
import "../shared"

Image {
    id: wall

    source: "images/brickwall.png"
    fillMode: Image.Tile

    BoxBody {
        world: physicsWorld
        target: wall

        width: wall.width
        height: wall.height
        friction: 1.0
    }
}
