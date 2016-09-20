import QtQuick 2.2
import Box2D 2.0
import Box2D.Components 1.0

ImageBoxBody {
    world: physicsWorld

    source: "qrc:/images/wall.jpg"
    fillMode: Image.Tile

    friction: 1
    density: 1
}
