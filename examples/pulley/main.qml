import QtQuick 2.2
import Box2D 2.0
import "../shared"

Rectangle {
    id: screen
    width: 800
    height: 600

    Component {
        id: ballComponent
        PhysicsItem {
            id: box
            width: 20
            height: 20
            bodyType: Body.Dynamic
            fixtures: Circle {
                radius: box.width / 2
                density: 10
                friction: 0.3
                restitution: 0.5
            }
            Rectangle {
                radius: parent.width / 2
                border.color: "blue"
                color: "#EFEFEF"
                anchors.fill: parent
            }
        }
    }

    World { id: physicsWorld; }

    Canvas {
        id: cords
        anchors.fill: parent
        onPaint: {
            var bodyACenter = bodyA.body.getWorldCenter();
            var bodyBCenter = bodyB.body.getWorldCenter();
            var context = cords.getContext("2d");
            context.clearRect(0, 0, width, height);
            context.beginPath();
            context.moveTo(225,100);
            context.lineTo(575,100);
            context.moveTo(bodyACenter.x, bodyACenter.y);
            context.lineTo(225,100);
            context.moveTo(bodyBCenter.x, bodyBCenter.y);
            context.lineTo(575,100);
            context.strokeStyle = "grey";
            context.stroke();
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
        id: limiterA
        x: 210
        y: 85
        width:30
        height: 30
        fixtures: Circle { radius: 15 }
        Rectangle {
            anchors.fill: parent
            radius: 15
            color: "green"
        }
    }

    PhysicsItem {
        id: limiterB
        x: 560
        y: 85
        width: 30
        height: 30
        fixtures: Circle { radius: 15 }
        Rectangle {
            anchors.fill: parent
            radius: 15
            color: "green"
        }
    }

    PhysicsItem {
        id: bodyA
        x: 125
        y: 300
        width: 200
        height: 100
        bodyType: Body.Dynamic
        fixtures: [
            Box {
                y: 40
                width: bodyA.width
                height: bodyA.height - 40
                density: 10
            },
            Box {
                x: 0
                y: 0
                width: 10
                height: 40
                density: 10
            },
            Box {
                x:190
                y: 0
                width: 10
                height: 40
                density: 10
            }
        ]
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: 40
            color:"#555555"
        }
        Rectangle {
            x: 0
            y: 0
            width: 10
            height: 40
            color: "#555555"
        }
        Rectangle {
            x: 190
            y: 0
            width: 10
            height: 40
            color: "#555555"
        }
        onXChanged: cords.requestPaint();
        onYChanged: cords.requestPaint();
    }
    PhysicsItem {
        id: bodyB
        x: 475
        y: 300
        width: 200
        height: 100
        bodyType: Body.Dynamic
        fixtures: [
            Box {
                y: 40
                width: bodyB.width
                height: bodyB.height - 40
                density: 10
            },
            Box {
                x: 0
                y: 0
                width: 10
                height: 40
                density: 10
            },
            Box {
                x: 190
                y: 0
                width: 10
                height: 40
                density: 10
            }
        ]
        Rectangle {
            anchors.fill: parent
            anchors.topMargin: 40
            color: "#555555"
        }
        Rectangle {
            x: 0
            y: 0
            width: 10
            height: 40
            color: "#555555"
        }
        Rectangle {
            x: 190
            y: 0
            width: 10
            height: 40
            color:"#555555"
        }
    }
    PulleyJoint {
        bodyA: bodyA.body
        bodyB: bodyB.body
        groundAnchorA: Qt.point(225,100)
        groundAnchorB: Qt.point(575,100)
        localAnchorA: Qt.point(100,0)
        localAnchorB: Qt.point(100,0)
        lengthA: 150
        lengthB: 150
    }

    PhysicsItem {
        id: floor
        x: 40
        y: 260
        width: 720
        height: 120
        fixtures: [
            Box {
                x: 0
                y: 0
                width: 84
                height: floor.height
                friction: 0.2
            },
            Box {
                x: 286
                y: 0
                width: 148
                height: floor.height
                friction: 0.2
            },
            Box {
                x: 636
                y: 0
                width: 84
                height: floor.height
                friction: 0.2
            }
        ]
        Rectangle {
            x: 0
            y: 0
            width: 84
            height: parent.height
            color: "#DEDEDE"
        }
        Rectangle {
            x: 286
            y: 0
            width: 148
            height: parent.height
            color: "#DEDEDE"
        }
        Rectangle {
            x: 636
            y: 0
            width: 84
            height: parent.height
            color: "#DEDEDE"
        }

    }

    PhysicsItem {
        id: triangle
        x: 370
        y: 500
        width: 60
        height: 60
        fixtures: Polygon {
            vertices: [
                Qt.point(30,0),
                Qt.point(0,60),
                Qt.point(60,60)
            ]
        }
        Canvas {
            id: canvas
            anchors.fill: parent
            onPaint: {
                var context = canvas.getContext("2d");
                context.beginPath();
                context.moveTo(parent.width / 2,0);
                context.lineTo(0,parent.height);
                context.lineTo(parent.width,parent.height);
                context.lineTo(parent.width / 2,0);
                context.fillStyle = "green";
                context.fill();
            }
        }
    }
    PhysicsItem {
        id: balancer
        x: 70
        y: 490
        width: 660
        height: 10
        bodyType: Body.Dynamic
        fixtures: Box {
            width: balancer.width
            height: balancer.height
            density: 10
            friction: 0.5
        }
        Rectangle {
            anchors.fill: parent
            color: "orange"
        }
    }

    PhysicsItem {
        id: circle
        x: 370
        y: 430
        width: 60
        height: 60
        bodyType: Body.Dynamic
        fixtures: Circle {
            radius: 30
            density: 20
            friction: 0.9
        }
        Rectangle {
            anchors.fill: parent
            radius: 30
            color:  "red"
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

    DebugDraw {
        id: debugDraw
        world: physicsWorld
        opacity: 1
        visible: false
    }

    Timer {
        id: ballsTimer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            var newBox = ballComponent.createObject(screen);
            newBox.x = 40 + Math.random() * screen.width - 80;
            newBox.y = 50;
            console.log(newBox.x, newBox.y)
        }
    }
}
