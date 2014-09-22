import QtQuick 2.2
import Box2D 2.0
import "../shared"

Rectangle {
    id: screen

    width: 800
    height: 600

    property int hz: 0

    Component {
        id: ballComponent

        PhysicsItem {
            id: box

            width: 20
            height: 20
            bodyType: Body.Dynamic

            fixtures: Circle {
                radius: box.width / 2
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

        PhysicsItem {
            id: link

            width: 20
            height: 20
            z: 1
            bodyType: Body.Dynamic

            fixtures: Box {
                width: link.width
                height: link.height
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
            frequencyHz: hz
        }
    }

    function createBranch(base,count) {
        var prevLink = base;
        var angle = Math.random() * 10 - 5;
        for (var i = 0; i < count; i++) {
            var newLink = linkComponent.createObject(screen);
            newLink.width = 20;
            newLink.height = 3 + count - i;
            if (count % 2) {
                newLink.x = prevLink.x + prevLink.width;
                newLink.y = prevLink.y - (prevLink.height / 2);
            } else {
                newLink.x = prevLink.x - newLink.width;
                newLink.y = prevLink.y - (prevLink.height / 2);
            }
            var newJoint = linkJoint.createObject(screen);
            if (count % 2) {
                newJoint.localAnchorA = Qt.point(prevLink.width, prevLink.height / 2);
                newJoint.localAnchorB = Qt.point(0, newLink.height / 2);
            } else {
                newJoint.localAnchorA = Qt.point(0, prevLink.height / 2);
                newJoint.localAnchorB = Qt.point(newLink.width, newLink.height / 2);
            }
            newJoint.referenceAngle = angle;
            newJoint.bodyA = prevLink.body;
            newJoint.bodyB = newLink.body;
            prevLink = newLink;
        }
    }

    World { id: physicsWorld }

    Component.onCompleted: {
        var prevLink = bodyA;
        for (var i = 0; i < 10; i++) {
            var newLink = linkComponent.createObject(screen);
            newLink.x = 350 + i * 3;
            newLink.y = 500 - (i * 40);
            newLink.width = 20 - i * 1.5;
            newLink.height = 40;
            var newJoint = linkJoint.createObject(screen);
            if (i == 0)
                newJoint.localAnchorA = Qt.point(bodyA.width / 2, 0);
            else
                newJoint.localAnchorA = Qt.point(newLink.width / 2, 0);
            newJoint.localAnchorB = Qt.point(newLink.width / 2, newLink.height);
            newJoint.bodyA = prevLink.body;
            newJoint.bodyB = newLink.body;
            prevLink = newLink;
            createBranch(newLink, 10 - i);
        }
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

    PhysicsItem {
        id: bodyA
        width: 100
        height: 20
        x: 300
        y: 540
        fixtures: Box {
            width: bodyA.width
            height: bodyA.height
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
                if (hz == 0) {
                    hz = 60;
                    crazyButton.color = "#999";
                } else {
                    hz = 0;
                    crazyButton.color = "#DEDEDE";
                }
            }
        }
    }

    DebugDraw {
        id: debugDraw
        world: physicsWorld
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
            var newBox = ballComponent.createObject(screen);
            newBox.x = 40 + (Math.random() * screen.width - 80);
            newBox.y = 50;
        }
    }
}
