import QtQuick
import Box2D
import "../shared"

ImageBoxBody {
    world: physicsWorld

    source: "images/wall.jpg"
    fillMode: Image.Tile

    friction: 1
    density: 1
}
