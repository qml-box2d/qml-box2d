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
        Rectangle {
            id: rectangle
            radius: width / 2
            width: 80
            height: 80
            smooth: true
            color: "black"

            CircleBody {
                target: rectangle
                world: physicsWorld
                bodyType: Body.Dynamic
                radius: 40
                density: 5
                friction: 0.3
                restitution: 0.2
            }
        }
    }

    // Timer that keeps creating heavy balls that crash down on the building
    Timer {
        running: true
        repeat: true
        interval: 1000
        onTriggered: {
            var ball = heavyBall.createObject(screen)
            ball.x =  Math.random() * screen.width
            ball.y = -100
        }
    }

    // BOX2D WORLD
    World { id: physicsWorld; }

    PhysicsItem {
        id: ground
        height: 20
        anchors { left: parent.left; right: parent.right; top: parent.bottom }
        fixtures: Box {
            height: ground.height
            width: ground.width
        }
    }


    Square {
        id: square
        x: 100
        y: 200
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

    PhysicsItem {
        id: middle
        anchors.centerIn: parent
    }

    PrismaticJoint {
        id: prismatic
        lowerTranslation: -250
        upperTranslation: 250
        enableLimit: true
        maxMotorForce: 3000
        motorSpeed: -100
        enableMotor: true
        bodyB: square.body
        bodyA: middle.body
        localAxisA: Qt.point(100, 40)
    }

    // Debug
    DebugDraw {
        id: debugDraw
        world: physicsWorld
        opacity: 0.75
        visible: false
    }
}
