import QtQuick 2.2
import Box2D 2.0
import "../shared"

ImageBoxBody {
    world: physicsWorld

    source: "images/wall.jpg"
    fillMode: Image.Tile

    friction: 1
    density: 1
}
