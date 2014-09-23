import QtQuick 2.0
import Box2D 2.0
import "../shared"

Item {
    id: screen
    width: 800
    height: 600
    focus: true

    Keys.onPressed: {
        if (event.key === Qt.Key_Left) {
            revolute.motorSpeed -= 10;
        }
        else if (event.key === Qt.Key_Right) {
            revolute.motorSpeed += 10
        }
    }

    Text {
        anchors {
            right: parent.right
            top: parent.top
            left: parent.left
        }
        height: 40
        horizontalAlignment: Text.AlignHCenter;
        text: "Left/Right buttons to control the speed, Mouse click to activate/deactivate motor"
    }

    // BOX2D WORLD
    World { id: physicsWorld }

    PhysicsItem {
        id: rod
        sleepingAllowed: false
        bodyType: Body.Dynamic
        x: 350
        y: 300

        width: 250
        height: 40

        fixtures: Box {
            width: rod.width
            height: rod.height
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

    PhysicsItem {
        id: middle

        x: 400
        y: 300

        fixtures: Circle { radius: itemShape.radius }

        Rectangle {
            id: itemShape
            radius: width / 2
            width: 40; height: 40
            color: "black"
        }
    }

    RevoluteJoint {
        id: revolute
        maxMotorTorque: 1000
        motorSpeed: 0
        enableMotor: false
        bodyA: middle.body
        bodyB: rod.body
        localAnchorA: Qt.point(20,20)
    }

    // Debug
    DebugDraw {
        id: debugDraw
        world: physicsWorld
        opacity: 0.5
        visible: false
    }

    MouseArea {
        anchors.fill: parent
        onClicked: revolute.enableMotor = !revolute.enableMotor
    }
}
