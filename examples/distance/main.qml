import QtQuick 2.0
import Box2D 2.0
import "../shared"

Item {
    id: screen
    width: 800
    height: 600
    focus: true

    // A heavy ball that will be created dynamically with the timer below
    Component {
        id: heavyBall
        PhysicsItem {
            bodyType: Body.Dynamic
            world: physicsWorld

			fixtures: Circle {
                id: circle
                radius: 40
                density: 5
                friction: 0.3
                restitution: 0.2
            }

            Rectangle {
                width: 80; height: 80
                radius: 40
                smooth: true
                color: "black"
            }
        }
    }

    Component {
        id: lightBall
        PhysicsItem {
			bodyType: Body.Dynamic
            world: physicsWorld

            fixtures: Circle {
                id: circle
                radius: 40
                density: 2
                friction: 0.3
                restitution: 0.2
            }

            Rectangle {
                width: 80; height: 80
                radius: 40
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
            var ball = heavyBall.createObject(screen)
            ball.x =  400
            ball.y = 50
            var ball2 = lightBall.createObject(screen)
            ball2.x =  150
            ball2.y = 50
            var joint = extraJoint.createObject(screen)
            joint.bodyA = ball.body
            joint.bodyB = ball2.body
        }
    }

    // BOX2D WORLD
    World { id: physicsWorld }

    ScreenBoundaries {}

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
        x: 180
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
        bodyA: ball.body
        bodyB: square.body
    }

    PhysicsItem {
        id: bar
        width: 300
        height: 50
        anchors.centerIn: parent

        fixtures: Box {
            width: bar.width
            height: bar.height
        }

        Rectangle {
            anchors.fill: parent
            radius: 6
            color: "black"
        }
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
