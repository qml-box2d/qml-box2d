import QtQuick 2.2
import Box2D 1.1


Rectangle {
    width: 800
    height: 600
    id: global

    Component {
        id: rectComponent
        Body {
            id: rect
            width: 20
            height: 20
            sleepingAllowed: true
            bodyType: Body.Dynamic
            property variant colors : ["#FF0000","#FF8000","#FFFF00","#00FF00","#0080FF","#0000FF","#FF00FF","#FFFFFF"]
            property int colorIndex : 0
            property bool animateDeletion: false
            function doDestroy() {
                destroy();
            }
            fixtures: Box {
                id: rectFixture
                property bool isBall: true
                anchors.fill: parent
                density: 0.5
                friction: 1
                restitution: 0.2
            }
            Rectangle {
                border.color: "#999"
                color: colors[colorIndex]
                width: parent.width
                height: parent.height
                radius: 3
            }
            PropertyAnimation {
                target: rect
                property: "opacity"
                duration: 1000
                to: 0
                easing.type: Easing.InCubic
                running: animateDeletion
                onRunningChanged: {
                    if(!running)
                        doDestroy();
                }
            }
        }
    }

    World {
        id: world
        anchors.fill: parent
        onPreSolve : {
            if(contact.fixtureA.isBall && contact.fixtureB === topBeltFixture)
                contact.tangentSpeed = -3.0;
            else if(contact.fixtureB.isBall && contact.fixtureA === topBeltFixture)
                contact.tangentSpeed = 3.0;
        }
        Body {
            id: topWall
            height: 10
            y: -10
            bodyType: Body.Static
            anchors {
                left: parent.left
                right: parent.right
            }
            fixtures: Box {
                anchors.fill: parent
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
            id: ground
            height: 40
            bodyType: Body.Static
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            fixtures: Box {
                id: groundFixture
                anchors.fill: parent
                friction: 1
                density: 1
            }
            Rectangle {
                anchors.fill: parent
                color: "#DEDEDE"
            }
        }

        Body {
            id: drivingWheel
            width: 48
            height: 48
            bodyType: Body.Dynamic
            fixtures: Circle {
                anchors.fill: parent
                radius: 24
                density: 0.5
            }
            Image {
                anchors.fill: parent
                source: "images/wheel.png"
            }
        }

        Body {
            id: drivenWheel
            width: 48
            height: 48
            bodyType: Body.Dynamic
            fixtures: Circle {
                anchors.fill: parent
                radius: 24
                density: 0.5
            }
            Image {
                anchors.fill: parent
                source: "images/wheel.png"
            }
        }

        Body {
            id: topBelt
            x: 65
            y: 500
            width: 600
            height: 5
            fixtures: Box {
                id: topBeltFixture
                anchors.fill: parent
                density: 0.5
            }
            Rectangle {
                anchors.fill: parent
                color: "#000"
                radius: 5
            }
        }
        Rectangle {
            id: bottomBelt
            x: 65
            y: 543
            width: 600
            height: 5
            color: "#000"
            radius: 5
        }

        RevoluteJoint {
            bodyA: topBelt
            bodyB: drivingWheel
            localAnchorA: Qt.point(600,24)
            localAnchorB: Qt.point(24,24)
            collideConnected: false
            enableMotor: true
            motorSpeed: 180
            maxMotorTorque: 100
        }

        RevoluteJoint {
            bodyA: topBelt
            bodyB: drivenWheel
            localAnchorA: Qt.point(0,24)
            localAnchorB: Qt.point(24,24)
            collideConnected: false
            enableMotor: true
            motorSpeed: 180
            maxMotorTorque: 100
        }
        Body {
            id: tube
            x: 500
            y: 10
            width: 250
            height: 450
            fixtures: [
                Chain {
                    vertices: [
                        Qt.point(0,60),
                        Qt.point(170,60),
                        Qt.point(180,70),
                        Qt.point(180,350),
                        Qt.point(170,400),
                        Qt.point(170,430)
                    ]
                },
                Chain {
                    vertices: [
                        Qt.point(0,5),
                        Qt.point(190,5),
                        Qt.point(225,25),
                        Qt.point(240,60),
                        Qt.point(240,350),
                        Qt.point(250,400),
                        Qt.point(250,430)
                    ]
                }
            ]
            Canvas {
                id: canvas
                anchors.fill: parent
                onPaint: {
                    var context = canvas.getContext("2d");
                    context.beginPath();
                    context.moveTo(0,60);
                    context.lineTo(170,60);
                    context.lineTo(180,70);
                    context.lineTo(180,350);
                    context.lineTo(170,400);
                    context.lineTo(170,430);
                    context.lineTo(250,430);
                    context.lineTo(250,400);
                    context.lineTo(240,350);
                    context.lineTo(240,60);
                    context.lineTo(225,25);
                    context.lineTo(190,5);
                    context.lineTo(0,5);
                    context.lineTo(0,60);
                    context.fillStyle = "#DEDEDE";
                    context.lineWidth = 1;
                    context.lineJoin = "miter";
                    context.fill();
                    context.strokeStyle = "#999";
                    context.stroke();
                }
            }
        }

        Body {
            id: flowVertical
            x: 680
            y: 60
            width: 60
            height: 500
            fixtures: Box {
                anchors.fill: parent
                sensor: true
                onBeginContact: {
                    other.parent.gravityScale = -2;
                }
            }
        }
        Body {
            id: flowHorizontal
            x: 500
            y: 10
            width: 240
            height: 60
            fixtures: Box {
                anchors.fill: parent
                sensor: true
                onContactChanged: {
                    other.parent.gravityScale = 0.5;
                    other.parent.applyForce(Qt.point(-5,0),Qt.point(24,24));
                }
                onEndContact: {
                    var body = other.parent;
                    body.gravityScale = 1;
                    body.applyForce(Qt.point(5,0),Qt.point(24,24));
                    var index = body.colorIndex;
                    index ++;
                    body.colorIndex = index;
                    if((index + 1) === body.colors.length)
                        body.animateDeletion = true;
                }
            }
        }

        Rectangle {
            id: debugButton
            x: 50
            y: 10
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

        Timer {
            id: rectTimer
            interval: 2000
            running: true
            repeat: true
            onTriggered: {
                var newBox = rectComponent.createObject(world);
                newBox.x = 60 + (Math.random() * 300);
                newBox.y = 200;
            }
        }

        DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: world
            opacity: 0.7
            visible: false
        }
    }
}
