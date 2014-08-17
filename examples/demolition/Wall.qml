import QtQuick 2.0
import "../shared"

ImageBoxBody {
    source: "images/brickwall.png"
    fillMode: Image.Tile

    world: physicsWorld
    friction: 1.0
}
