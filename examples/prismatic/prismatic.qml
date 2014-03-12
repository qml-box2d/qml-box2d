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
            width: 80
			height: 80
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

    // Timer that keeps creating heavy balls that crash down on the building
    Timer {
        running: true
        repeat: true
        interval: 1000
        onTriggered: {
            var ball = heavyBall.createObject(world)
            ball.x =  Math.random() * world.width
            ball.y = -100
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

        Square {
            id: square
            x: 300
            y: 400
            rotation: 0
            width: 200
            height: 80

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    prismatic.motorSpeed *= -1
                }
            }
        }

        Body {
            id: middle
            bodyType: Body.Static

            anchors.centerIn: parent
        }

        PrismaticJoint {
            id: prismatic
            lowerTranslation: -250
            upperTranslation: 150
            enableLimit: true
            maxMotorForce: 3000
            motorSpeed: -100
            enableMotor: true
            bodyB: square
            bodyA: middle
            axis: Qt.point(100, 40)
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
}
