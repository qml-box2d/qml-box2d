import Qt 4.7
import Box2D 1.0

Item {
    id: screen
    width: 800
    height: 600
    focus: true

    // BOX2D WORLD
    World {
        id: world;
        anchors.fill: parent

        Wall {
            id: ground
            height: 20
            anchors { left: parent.left; right: parent.right; top: parent.bottom }
        }
        Wall {
            id: ceiling
            height: 20
            anchors { left: parent.left; right: parent.right; bottom: parent.top }
        }
        Wall {
            id: leftWall
            width: 20
            anchors { right: parent.left; bottom: ground.top; top: ceiling.bottom }
        }
        Wall {
            id: rightWall
            width: 20
            anchors { left: parent.right; bottom: ground.top; top: ceiling.bottom }
        }

        Ball {
            id: ball
            x: 100
            y: 100
            rotation: 0
            width: 80
            height: 80

            Component.onCompleted: joint.bodyA = ball
        }

        Square {
            id: square
            x: 120
            y: 120
            rotation: 0
            width: 80
            height: 80

            Component.onCompleted: joint.bodyB = square
        }

        DistanceJoint {
            id: joint
            frequencyHz: 15
            dampingRatio: 0.5
            collideConnected: true
        }

        Body {
            bodyType: Body.Static
            width: 300
            height: 50
            anchors.centerIn: parent
            fixtures: Box { anchors.fill: parent }

            Rectangle {
                anchors.fill: parent
                radius: 6
                color: "black"
            }
        }

        // Debug
        DebugDraw {
            id: debugDraw
            world: world
            anchors.fill: world
            opacity: 0.75
            visible: false
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ball.applyLinearImpulse(
                            Qt.point(40 * (mouseX - ball.x),
                                     40 * (mouseY - ball.y)),
                            Qt.point(ball.x, ball.y))
            }
        }
    }
}
