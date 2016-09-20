import QtQuick 2.2
import Box2D.Components 1.0

ImageBoxBody {
    source: "qrc:/images/wall.jpg"
    fillMode: Image.Tile

    world: physicsWorld

    friction: 1
    density: 1
}
