import QtQuick 2.2
import "../shared"

ImageBoxBody {
    source: "images/wall.jpg"
    fillMode: Image.Tile

    world: physicsWorld

    friction: 1
    density: 1
}
