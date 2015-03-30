import QtQuick 2.2
import Box2D 2.0
import "../shared"

Rectangle {
    id: screen

    width: 800
    height: 600
    color: "#EFEFFF"

    Component {
        id: frictionJoint
        FrictionJoint {
            bodyA: anchor.body
            maxForce: 0.5
            maxTorque: 0.5
            localAnchorA: Qt.point(10, 10)
            localAnchorB: Qt.point(10, 10)
        }
    }

    Component {
        id: boxComponent
        RectangleBoxBody {
            id: box

            width: 20
            height: 20
            border.color: "blue"
            color: "#EFEFEF"
            smooth: true
            antialiasing: true

            world: physicsWorld
            bodyType: Body.Dynamic

            density: 0.1
            friction: 1
            restitution: 0.5
        }
    }

    World {
        id: physicsWorld
        gravity: Qt.point(0.0, 0.0);
    }

    Wall {
        id: topWall
        height: 40
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
    }

    Wall {
        id: leftWall
        width: 40
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 40
        }
    }

    Wall {
        id: rightWall
        width: 40
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 40
        }
    }
    Wall {
        id: bottomWall
        height: 40
        anchors {
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }
    }

    RectangleBoxBody {
        id: anchor
        anchors.centerIn: parent
        width: 20
        height: 20
        color: "green"
        world: physicsWorld
    }

    Rectangle {
        id: debugButton
        x: 50
        y: 50
        width: 120
        height: 30
        Text {
            text: debugDraw.visible ? "Debug view: on" : "Debug view: off";
            anchors.centerIn: parent
        }
        color: "#DEDEDE"
        border.color: "#999"
        radius: 5
        MouseArea {
            anchors.fill: parent
            onClicked: debugDraw.visible = !debugDraw.visible;
        }
    }

    DebugDraw {
        id: debugDraw
        anchors.fill: parent
        world: physicsWorld
        opacity: 1
        visible: false
    }

    Timer {
        id: ballsTimer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            var newBox = boxComponent.createObject(screen);
            newBox.x = screen.width / 2 - 10;
            newBox.y = screen.height / 2 - 10;
            var x = ((Math.random() * 800) - 400) / 200;
            var y = ((Math.random() * 600) - 300) / 200;
            if (Math.round(Math.random() * 5) == 1) {
                newBox.border.color = "red";
            } else {
                var joint = frictionJoint.createObject(screen);
                joint.bodyB = newBox.body;
            }
            newBox.body.applyLinearImpulse(Qt.point(x,y), Qt.point(10,10));
        }
    }
}
