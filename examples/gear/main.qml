import QtQuick 2.2
import Box2D 1.1


Rectangle {
    width: 800
    height: 600

    Component {
        id: ballComponent
        Body {
            id: box
            width: 20
            height:20
            property string color: "#EFEFEF"
            sleepingAllowed: true
			bodyType: Body.Dynamic
            fixtures: Circle {
                radius: parent.width / 2
                anchors.centerIn: parent
                density: 0.1
                friction: 10
                restitution: 0.5
            }
            Rectangle {
                radius: parent.width / 2
                border.color: "blue"
                color: parent.color
                width: parent.width
                height: parent.height
            }
        }
    }

    World {
        id: world
        anchors.fill: parent

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
            id: prop
            height: 150
            y: 200
            bodyType: Body.Static
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 40
            anchors.rightMargin: 40
            fixtures: [
                Polygon {
                    vertices: [
                        Qt.point(0,0),
                        Qt.point(10,5),
                        Qt.point(60,150),
                        Qt.point(0,150)
                    ]
                    density: 0.5
                    friction: 0
                },
                Polygon {
                    vertices: [
                        Qt.point(110,50),
                        Qt.point(130,5),
                        Qt.point(350,0),
                        Qt.point(565,5),
                        Qt.point(585,50)
                    ]
                    density: 0.5
                    friction: 0
                },
                Polygon {
                    vertices: [
                        Qt.point(610,50),
                        Qt.point(630,5),
                        Qt.point(720,0),
                        Qt.point(720,50)
                    ]
                    density: 0.5
                    friction: 0
                }
            ]
            Canvas {
                id: propCanvas
                anchors.fill: parent
                onPaint: {
                    var context = propCanvas.getContext("2d");
                    context.beginPath();
                    var fixtures = prop.fixtures;
                    var count = fixtures.count;
                    for(var i = 0;i < fixtures.length;i ++) {
                        var fixture = fixtures[i];
                        var vertices = fixture.vertices;
                        context.moveTo(vertices[0].x,vertices[0].y);
                        for(var j = 1;j < vertices.length;j ++) {
                            context.lineTo(vertices[j].x,vertices[j].y);
                        }
                        context.lineTo(vertices[0].x,vertices[0].y);
                    }
                    context.fillStyle = "#488AC7";
                    context.fill();
                }
            }
        }

        Body {
            id: lever
            x: 100
            y: 250
            width: 100
            height: 100
            bodyType: Body.Dynamic
            fixtures: Polygon {
                anchors.fill: parent
                vertices: [
                    Qt.point(50,0),
                    Qt.point(parent.width,parent.height),
                    Qt.point(10,parent.height)
                ]
                density: 0.2
                friction: 10
            }
            Canvas {
                id: leverCanvas
                anchors.fill: parent
                onPaint: {
                    var context = leverCanvas.getContext("2d");
                    context.beginPath();
                    context.moveTo(50,0);
                    context.lineTo(parent.width,parent.height);
                    context.lineTo(10,parent.height);
                    context.lineTo(50,0);
                    context.fillStyle = "#89C35C";
                    context.fill();
                }
            }
        }

        RevoluteJoint {
            id: revoluteJoint
            world: world
            bodyA: prop
            bodyB: lever
            localAnchorA: Qt.point(110,50)
            localAnchorB: Qt.point(50,0)
        }

        Body {
            id: damper
            x: 650
            y: 260
            width: 110
            height: 20
            bodyType: Body.Dynamic
            fixtures: Box {
                anchors.fill: parent
                density: 0.1
                friction: 10
            }
            Rectangle {
                anchors.fill: parent
                color: "#C88141"
            }
        }

        PrismaticJoint {
            id: prismaticJoint
            world: world
            bodyA: prop
            bodyB: damper
            localAnchorA: Qt.point(610,50)
            localAnchorB: Qt.point(0,-1)
            axis: Qt.point(100,0)
            collideConnected: true
            enableLimit: true
            lowerTranslation: -110
            upperTranslation: 0
        }

        GearJoint {
            id: gearJoint
            world: world
            bodyA: lever
            bodyB: damper
            joint1: revoluteJoint
            joint2: prismaticJoint
            ratio: 0.05
        }

        Body {
            id: mixerLeft
            x: 90
            y: 500
            width: 10
            height: 50
			bodyType: Body.Dynamic
            fixtures: Box {
                anchors.fill: parent
                density: 0.5
            }
            Rectangle {
                anchors.fill: parent
                color: "brown"
            }
        }

        RevoluteJoint {
            id: mixerLeftJoint
            world: world
            bodyA: leftWall
            bodyB: mixerLeft
            localAnchorA: Qt.point(100,500)
            localAnchorB: Qt.point(5,0)
        }

        Body {
            id: mixerRight
            x: 710
            y: 500
            width: 10
            height: 50
			bodyType: Body.Dynamic
            fixtures: Box {
                anchors.fill: parent
                density: 0.5
            }
            Rectangle {
                anchors.fill: parent
                color: "brown"
            }
        }

        RevoluteJoint {
            id: mixerRightJoint
            world: world
            bodyA: rightWall
            bodyB: mixerRight
            localAnchorA: Qt.point(-60,500)
            localAnchorB: Qt.point(5,0)
            enableMotor: true
            motorSpeed: 90
            maxMotorTorque: 10000
        }
        GearJoint {
            id: mixerJoint
            world: world
            bodyA: mixerLeft
            bodyB: mixerRight
            joint1:mixerLeftJoint
            joint2: mixerRightJoint
            ratio: 1
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

        Body {
            id: leftSensor
            x:40
            y: 360
            width: 360
            height:20
            bodyType: Body.Static
            fixtures: Box {
                anchors.fill: parent
                sensor: true
                onBeginContact: {
                    if(other.GetBody().color === "#EFEFEF")
                    {
                        other.GetBody().color = "lightgreen"
                        leftCounter.count ++;
                    }
                }
            }
        }

        Body {
            id: rightSensor
            x:400
            y: 360
            width: 360
            height:20
            bodyType: Body.Static
            fixtures: Box {
                anchors.fill: parent
                sensor: true
                onBeginContact: {
                    if(other.GetBody().color === "#EFEFEF") {
                        other.GetBody().color = "orange"
                        rightCounter.count ++;
                    }
                }
            }
        }

        Text {
            id: leftCounter
            property int count: 0
            x:300
            y: 220
            width: 75
            height: 20
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            text: leftCounter.count
        }

        Text {
            id: rightCounter
            property int count: 0
            x:410
            y: 220
            width: 75
            height: 20
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            text: rightCounter.count
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
            interval: 2000
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
