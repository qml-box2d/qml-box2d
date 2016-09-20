import QtQuick 2.0
import Box2D.Components 1.0

ImageBoxBody {
    source: "qrc:/images/brickwall.png"
    fillMode: Image.Tile

    world: physicsWorld
    friction: 1.0
}
