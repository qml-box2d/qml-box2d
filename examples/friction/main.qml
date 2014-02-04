import QtQuick 2.2
import Box2D 1.1

Rectangle {
    width: 800
    height: 600
    color: "#EFEFFF"

    Component
    {
        id: frictionJoint
        FrictionJoint {
            bodyA: anchor
            maxForce: 0.5
            maxTorque: 0.5
            localAnchorA: Qt.point(10,10)
            localAnchorB: Qt.point(10,10)
        }
    }

    Component {
        id: boxComponent
        Body {
            id: box
            width: 20
            height:20
            sleepingAllowed: true
            property color boxColor: "blue"
			bodyType: Body.Dynamic
            fixtures: Box {
                anchors.fill: parent
                density: 0.1
                friction: 1
                restitution: 0.5
            }
            Rectangle {
                border.color: parent.boxColor
                color: "#EFEFEF"
                width: parent.width
                height: parent.height
                smooth: true
            }
        }
    }
    World {
        id: world
        anchors.fill: parent
        gravity: Qt.point(0.0,0.0);
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

        Body {
            id:  anchor
            x: world.width / 2
            y: world.height / 2
            width: 20
            height: 20
            bodyType: Body.Static
            Rectangle {
                anchors.fill: parent
                color: "green"
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
                text: "Debug view: off"
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
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                var newBox = boxComponent.createObject(world);
                newBox.x = world.width / 2;
                newBox.y = world.height / 2;
                var x = ((Math.random() * 800) - 400) / 15;
                var y = ((Math.random() * 600) - 300) / 15;
                if(Math.round(Math.random() * 5) == 1) {
                    newBox.boxColor = "red";
                }
                else {
                    var joint = frictionJoint.createObject(world);
                    joint.world = world;
                    joint.bodyB = newBox;
                }
                newBox.applyLinearImpulse(Qt.point(x,y),Qt.point(10,10));
            }
        }
    }
}
