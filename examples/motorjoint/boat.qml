import QtQuick 2.2
import Box2D 2.0
import "../shared"

Rectangle {
    width: 800
    height: 600

    World {
        id: physicsWorld

        onStepped: {
            joint.step += 0.2;
            if (joint.step > width - 150)
                joint.step = 0;
            joint.linearOffset = Qt.point(joint.step + 100, Math.sin(joint.step * 6.0));
            joint.angularOffset = Math.sin(joint.step / 8.0) * 10.0;
        }
    }

    Rectangle {
        id:waves
        height:30
        y: 260
        anchors {
            left: parent.left
            right: parent.right
        }
        Image {
            id: waveImg
            source: "images/wave.png"
            fillMode: Image.Tile
            anchors.fill: parent
        }
    }

    Rectangle {
        id: water
        y: 290
        height: parent.height - 290
        anchors {
            left: parent.left
            right: parent.right
        }
        color: "#74c2e6"
    }

    PhysicsItem {
        id: berth
        height: 30
        width: 100
        x: 0
        y: 260
        fixtures: Box {
            width: berth.width
            height: berth.height
        }
        Rectangle {
            anchors.fill: parent
            color: "brown"
        }
    }

    PhysicsItem {
        id: boat
        width: 32
        height: 32
        x: 100
        y: 250
        bodyType: Body.Dynamic
        fixtures: Box {
            width: boat.width
            height: boat.height
            friction: 0.6
            density: 2

        }
        Image {
            id: boatImg
            source: "images/boat.png"
            anchors.fill: parent
        }
    }

    MotorJoint {
        id: joint
        bodyA: berth.body
        bodyB: boat.body
        maxForce: 1000
        maxTorque: 1000
        property double step: 0.0
        angularOffset: 0
    }

    Rectangle {
        id: button
        x: 10
        y: 10
        width: 100
        height: 40
        color: "#DEDEDE"
        border.color: "#999"
        radius: 5
        Text {
            id: title
            text: debugDraw.visible ? "Debug view: on" : "Debug view: off"
            anchors.centerIn: parent
            anchors.margins: 5
        }
        MouseArea {
            anchors.fill: parent
            onClicked: debugDraw.visible = !debugDraw.visible;
        }
    }

    DebugDraw {
        id: debugDraw
        world: physicsWorld
        visible: false
    }
}
