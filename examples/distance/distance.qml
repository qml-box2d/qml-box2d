import QtQuick 2.0
import Box2D 1.1

Item {
    id: screen
    width: 800
    height: 600
    focus: true

    // A heavy ball that will be created dynamically with the timer below
    Component {
        id: heavyBall
        Body {
            bodyType: Body.Dynamic
			fixtures: Circle {
                radius: 40
                density: 5
                friction: 0.3
                restitution: 0.2
            }
            Rectangle {
                anchors.centerIn: parent
                radius: 40
                width: 80
                height: 80
                smooth: true
                color: "black"
            }
        }
    }

    Component {
        id: lightBall
        Body {
			bodyType: Body.Dynamic
            fixtures: Circle {
                radius: 40
                density: 2
                friction: 0.3
                restitution: 0.2
            }

            Rectangle {
                anchors.centerIn: parent
                radius: 40
                width: 80
                height: 80
                smooth: true
                color: "black"
            }
        }
    }

    Component {
        id: extraJoint
        DistanceJoint {
            frequencyHz: 20
            dampingRatio: 0.5
            collideConnected: false
        }
    }

    // Timer that keeps creating heavy balls that crash down on the building
    Timer {
        running: true
        repeat: false
        interval: 4000
        onTriggered: {
            var ball = heavyBall.createObject(world)
            ball.x =  400
            ball.y = 50
            var ball2 = lightBall.createObject(world)
            ball2.x =  150
            ball2.y = 50
            var joint = extraJoint.createObject(world)
            joint.bodyA = ball
            joint.bodyB = ball2
            joint.world = world
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

        Ball {
            id: ball
            x: 100
            y: 100
            rotation: 0
            width: 80
            height: 80
        }

        Square {
            id: square
            x: 120
            y: 120
            rotation: 0
            width: 80
            height: 80
        }

        DistanceJoint {
            id: joint
            frequencyHz: 15
            dampingRatio: 0.5
            collideConnected: true
            bodyA: ball
            bodyB: square
            world: world
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
                            Qt.point(10 * (mouseX - ball.x),
                                     10 * (mouseY - ball.y)),
                            Qt.point(ball.x, ball.y))
            }
        }
    }
}
