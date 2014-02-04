import QtQuick 2.2
import Box2D 1.1

Rectangle {
    width: 800
    height: 600
    id: global
    property int hz: 0

    Component {
        id: ballComponent
        Body {
            id: box
            width: 20
            height:20
            sleepingAllowed: true
			bodyType: Body.Dynamic;
            fixtures: Circle {
                radius: parent.width / 2
                anchors.centerIn: parent
                density: 0.1
                friction: 0.3
                restitution: 0.5
            }
            Rectangle {
                radius: parent.width / 2
                border.color: "blue"
                color: "#EFEFEF"
                width: parent.width
                height: parent.height
            }
        }
    }
    Component {
        id: linkComponent
        Body {
            width: 20
            height: 20
			z: 1
            bodyType: Body.Dynamic
            fixtures: Box {
                anchors.fill: parent
                density: 0.2
                friction: 0.3
            }
            Rectangle {
                anchors.fill: parent
                border.color: "#DEDEDE"
                color: "#44A51C"
            }
        }
    }

    Component {
        id: linkJoint
        WeldJoint {
            dampingRatio: 0.5
            frequencyHz: global.hz
        }
    }

    World {
        id: world
        anchors.fill: parent
        function createBranch(base,count) {
            var prevLink = base;
            var angle = Math.random() * 10 - 5;
            for(var i = 0;i < count;i ++) {
                var newLink = linkComponent.createObject(world);
                newLink.width = 20;
                newLink.height = 3 + count - i;
                if(count % 2) {
                    newLink.x = prevLink.x + prevLink.width;
                    newLink.y = prevLink.y - (prevLink.height / 2);
                }
                else {
                    newLink.x = prevLink.x - newLink.width;
                    newLink.y = prevLink.y - (prevLink.height / 2);
                }
                var newJoint = linkJoint.createObject(world);
                newJoint.world = world;
                if(count % 2) {
                    newJoint.localAnchorA = Qt.point(prevLink.width,prevLink.height / 2);
                    newJoint.localAnchorB = Qt.point(0,newLink.height / 2);
                }
                else {
                    newJoint.localAnchorA = Qt.point(0,prevLink.height / 2);
                    newJoint.localAnchorB = Qt.point(newLink.width,newLink.height / 2);
                }
                newJoint.referenceAngle = angle;
                newJoint.bodyA = prevLink;
                newJoint.bodyB = newLink;
                prevLink = newLink;
            }
        }

        onInitialized: {
            var prevLink = bodyA;
            for(var i = 0;i < 10;i ++) {
                var newLink = linkComponent.createObject(world);
                newLink.x = 350 + i * 3;
                newLink.y = 500 - (i * 40);
                newLink.width = 20 - i * 1.5;
                newLink.height = 40;
                var newJoint = linkJoint.createObject(world);
                newJoint.world = world;
                if(i == 0) newJoint.localAnchorA = Qt.point(bodyA.width / 2,0);
                else newJoint.localAnchorA = Qt.point(newLink.width / 2,0);
                newJoint.localAnchorB = Qt.point(newLink.width / 2,newLink.height);
                newJoint.bodyA = prevLink;
                newJoint.bodyB = newLink;
                prevLink = newLink;
                createBranch(newLink,10 - i);
            }
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

        Body {
            id: bodyA
            bodyType: Body.Static
            width: 100
            height: 20
            x: 300
            y: 540
            fixtures: Box {
                anchors.fill: parent
            }
            Rectangle {
                anchors.fill: parent
                color: "black"
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
        Rectangle {
            id: crazyButton
            x: 180
            y: 50
            width: 70
            height: 30
            Text {
                text: "Get crazy"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(global.hz == 0) {
                        global.hz = 60;
                        crazyButton.color = "#999";
                    }
                    else {
                        global.hz = 0;
                        crazyButton.color = "#DEDEDE";
                    }
                }
            }
        }

        DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: world
            opacity: 1
            visible: false
			z: 10
        }

        Timer {
            id: ballsTimer
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                var newBox = ballComponent.createObject(world);
                newBox.x = 40 + (Math.random() * world.width - 80);
                newBox.y = 50;
            }
        }
    }
}
