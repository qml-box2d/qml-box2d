import Qt 4.7
import Box2D 1.0

Item {
    id: screen
    width: 800
    height: 600
    focus: true
    Keys.onPressed: onKeysPressed(event)

    function onKeysPressed(event) {
        if (event.key == Qt.Key_Left) {
            revolute.motorSpeed -= 5
        }
        else if (event.key == Qt.Key_Right) {
            revolute.motorSpeed += 5
        }
    }

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

        Body {
            id: rod
            fixedRotation: false
            sleepingAllowed: false

            x: 350
            y: 300 - circleShape.radius

            width: 250
            height: 40

            fixtures: Box {
                anchors.fill: parent
                density: 1;
                friction: 1;
                restitution: 0.3;
            }

            Rectangle {
                color: "green"
                radius: 6
                anchors.fill: parent
            }
        }

        Body {
            id: middle
            fixedRotation: true
            sleepingAllowed: false
            bodyType: Body.Static

            width: 40
            height: width

            x: 400
            y: 300

            fixtures: Circle {
                id: circleShape
                radius: width / 2
                anchors.fill: parent
            }

            Rectangle {
                id: itemShape
                radius: 180
                width: parent.width
                height: parent.height
                color: "black"
                x: circleShape.x - circleShape.radius
                y: circleShape.y - circleShape.radius
            }
        }

        RevoluteJoint {
            id: revolute
            maxMotorTorque: 300
            motorSpeed: 0
            bodyA: middle
            bodyB: rod
            world: world
        }

        // Debug
        DebugDraw {
            id: debugDraw
            world: world
            anchors.fill: world
            opacity: 0.75
            visible: false
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: revolute.enableMotor = !revolute.enableMotor
    }
}
