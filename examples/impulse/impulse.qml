import QtQuick 2.0
import Box2D 2.0
import "../shared"

Item {
    id: screen
    width: 800
    height: 600
    focus: true

    // BOX2D WORLD
    World { id: physicsWorld }

    ScreenBoundaries {}

    Ball {
        id: ball
        x: parent.width / 2
        y: parent.height / 2
    }

    // Debug
    DebugDraw {
        id: debugDraw
        world: physicsWorld
        opacity: 0.75
        visible: false
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            ball.body.applyLinearImpulse(
                        Qt.point((mouseX - ball.x),
                                 (mouseY - ball.y)),
                        Qt.point(ball.x, ball.y))
        }
    }
}
