import QtQuick 2.2
import Box2D 2.0
import QtQuick.Controls 1.1
import "../shared"

Rectangle {
    id: screen

    width: 800
    height: 600

    Slider {
        id: lengthSlider
        x: 180
        y: 50
        width: 100
        height: 50
        maximumValue: 50
        minimumValue: 20
        value: 30
    }

    Component {
        id: linkComponent
        PhysicsItem {
            id: ball

            width: 20
            height: 20
            bodyType: Body.Dynamic

            property color color: "#EFEFEF"

            fixtures: Circle {
                radius: ball.width / 2
                density: 0.5
            }

            Rectangle {
                radius: parent.width / 2
                border.color: "blue"
                color: parent.color
                width: parent.width
                height: parent.height
                smooth: true
            }
        }
    }

    Component {
        id: jointComponent
        RopeJoint {
            localAnchorA: Qt.point(10,10)
            localAnchorB: Qt.point(10,10)
            maxLength: lengthSlider.value
            collideConnected: true
        }
    }

    World { id: physicsWorld }

    Component.onCompleted: {
        var prev = leftWall;
        for (var i = 60;i < 740;i += 20) {
            var newLink = linkComponent.createObject(screen);
            newLink.color = "orange";
            newLink.x = i;
            newLink.y = 100;
            var newJoint = jointComponent.createObject(screen);
            if (i === 60)
                newJoint.localAnchorA = Qt.point(40, 100);
            newJoint.bodyA = prev.body;
            newJoint.bodyB = newLink.body;
            prev = newLink;
        }
        newJoint = jointComponent.createObject(screen);
        newJoint.localAnchorB = Qt.point(0,100);
        newJoint.bodyA = prev.body;
        newJoint.bodyB = rightWall.body;
    }

    PhysicsItem {
        id: ground
        height: 40
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        fixtures: Box {
            width: ground.width
            height: ground.height
            friction: 1
            density: 1
        }
        Rectangle {
            anchors.fill: parent
            color: "#DEDEDE"
        }
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

    Rectangle {
        id: debugButton
        x: 50
        y: 50
        width: 120
        height: 30
        Text {
            text: "Debug view: " + (debugDraw.visible ? "on" : "off")
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
            var newBox = linkComponent.createObject(screen);
            newBox.x = 40 + (Math.random() * screen.width - 80);
            newBox.y = 50;
        }
    }
}
