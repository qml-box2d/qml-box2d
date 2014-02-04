import QtQuick 2.2
import Box2D 1.1
import QtQuick.Controls 1.1

Rectangle {
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
        Body {
            width: 20
            height:20
            sleepingAllowed: true
			bodyType: Body.Dynamic;
            property color color: "#EFEFEF"
            fixtures: Circle {
                radius: parent.width / 2
                anchors.centerIn: parent
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

    World {
        id: world
        anchors.fill: parent
        onInitialized: {
            var prev = leftWall;
            for(var i = 60;i < 740;i += 20) {
                var newLink = linkComponent.createObject(world);
                newLink.color = "orange";
                newLink.x = i;
                newLink.y = 100;
                var newJoint = jointComponent.createObject(world);
                if(i === 60) newJoint.localAnchorA = Qt.point(40,100);
                newJoint.world = world;
                newJoint.bodyA = prev;
                newJoint.bodyB = newLink;
                prev = newLink;
            }
            newJoint = jointComponent.createObject(world);
            newJoint.localAnchorB = Qt.point(0,100);
            newJoint.world = world;
            newJoint.bodyA = prev;
            newJoint.bodyB = rightWall;
        }

        Body {
            id: ground
            height: 40
            bodyType: Body.Static
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            fixtures: Box {
                anchors.fill: parent
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
                id: debugButtonText
                text: "Debug view: " + (debugDraw.visible ? "on" : "off")
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    debugDraw.visible = !debugDraw.visible;
                    debugButtonText.text = debugDraw.visible ? "Debug view: on" : "Debug view: off";
                }
            }
        }

        DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: world
            opacity: 1
            visible: false
        }

        Timer {
            id: ballsTimer
            interval: 500
            running: true
            repeat: true
            onTriggered: {
                var newBox = linkComponent.createObject(world);
                newBox.x = 40 + (Math.random() * world.width - 80);
                newBox.y = 50;
            }
        }
    }
}
