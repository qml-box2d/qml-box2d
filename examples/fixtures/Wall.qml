import QtQuick
import Box2D
import "../shared"

ImageBoxBody {
    source: "images/wall.jpg"
    fillMode: Image.Tile

    world: physicsWorld

    friction: 1
    density: 1
}
