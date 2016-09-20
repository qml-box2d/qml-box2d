import QtQuick 2.0
import Box2D.Components 1.0

Item {
    id: wall

    BoxBody {
        target: wall
        world: physicsWorld

        width: wall.width
        height: wall.height
    }
}
