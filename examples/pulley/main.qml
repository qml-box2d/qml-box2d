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
			bodyType: Body.Dynamic
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
    World {
        id: world
        property double step: 0.0
        anchors.fill: parent

        Canvas {
            id: cords
            anchors.fill: parent
            onPaint: {
                var x = bodyA.x + 100
                var y = bodyA.y
                var context = cords.getContext("2d");
                context.clearRect (0, 0, width, height);
                context.beginPath();
                context.moveTo(225,100);
                context.lineTo(575,100);
                context.moveTo(x,y);
                context.lineTo(225,100);
                x = bodyB.x + 100
                y = bodyB.y
                context.moveTo(x,y);
                context.lineTo(575,100);
                context.strokeStyle = "grey";
                context.stroke();
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
            id: limiterA
            bodyType: Body.Static
            x: 210
            y: 85
            width:30
            height: 30
            fixtures: Circle {
                anchors.fill: parent
                radius: 15
            }
            Rectangle {
                anchors.fill: parent
                radius: 15
                color: "green"
            }
        }

        Body {
            id: limiterB
            bodyType: Body.Static
            x: 560
            y: 85
            width:30
            height: 30
            fixtures: Circle {
                anchors.fill: parent
                radius: 15
            }
            Rectangle {
                anchors.fill: parent
                radius: 15
                color: "green"
            }
        }

        Body {
            id: bodyA
            x: 125
            y: 300
            width: 200
            height: 100
			bodyType: Body.Dynamic
            fixtures: [
                Box {
                    anchors.fill: parent
                    anchors.topMargin: 40
                },
                Box {
                    x:0
                    y: 0
                    width: 10
                    height: 40
                },
                Box {
                    x:190
                    y: 0
                    width: 10
                    height: 40
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
                color:"#555555"
            }
            Rectangle {
                x: 190
                y: 0
                width: 10
                height: 40
                color:"#555555"
            }
            onXChanged: {
                cords.requestPaint();
            }
            onYChanged: {
                cords.requestPaint();
            }
        }
        Body {
            id: bodyB
            x: 475
            y: 300
            width: 200
            height: 100
			bodyType: Body.Dynamic
            fixtures: [
                Box {
                    anchors.fill: parent
                    anchors.topMargin: 40
                },
                Box {
                    x:0
                    y: 0
                    width: 10
                    height: 40
                },
                Box {
                    x:190
                    y: 0
                    width: 10
                    height: 40
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
                color:"#555555"
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
            world: world
            bodyA: bodyA
            bodyB: bodyB
            groundAnchorA: Qt.point(225,100)
            groundAnchorB: Qt.point(575,100)
            localAnchorA: Qt.point(100,0)
            localAnchorB: Qt.point(100,0)
            lengthA: 150
            lengthB: 150
            ratio: 1
        }

        Body {
            id: floor
            x: 40
            y: 260
            width: 720
            height: 120
            bodyType: Body.Static
            fixtures: [
                Box {
                    x: 0
                    y: 0
                    width: 84
                    height: parent.height
                    friction: 0.2
                    density: 0.8
                },
                Box {
                    x: 286
                    y: 0
                    width: 148
                    height: parent.height
                    friction: 0.2
                    density: 0.8
                },
                Box {
                    x: 636
                    y: 0
                    width: 84
                    height: parent.height
                    friction: 0.2
                    density: 0.8
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

        Body {
            id: triangle
            x: 370
            y: 500
            width: 60
            height: 60
            bodyType: Body.Static
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
        Body {
            id: balancer
            x: 70
            y: 490
            width: 660
            height: 10
            bodyType: Body.Dynamic
            fixtures: Box {
                anchors.fill: parent
                density: 0.3
                friction: 0.5
            }
            Rectangle {
                anchors.fill: parent
                color: "orange"
            }
        }

        Body {
            id: circle
            x: 370
            y: 430
            width: 60
            height: 60
			bodyType: Body.Dynamic
            fixtures: Circle {
                anchors.fill: parent
                radius: 30
                density: 0.8
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
                var newBox = ballComponent.createObject(world);
                newBox.x = 40 + (Math.random() * world.width - 80);
                newBox.y = 50;


            }
        }
    }
}
