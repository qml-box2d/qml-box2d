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
            property string color: "#EFEFEF"
            bodyType: Body.Dynamic
            fixtures: Circle {
                radius: box.width / 2
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

    World { id: physicsWorld }

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
        id: prop
        height: 150
        y: 200
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

    PhysicsItem {
        id: lever
        x: 100
        y: 250
        width: 100
        height: 100
        bodyType: Body.Dynamic
        fixtures: Polygon {
            vertices: [
                Qt.point(50, 0),
                Qt.point(lever.width, lever.height),
                Qt.point(10, lever.height)
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
                context.moveTo(50, 0);
                context.lineTo(parent.width, parent.height);
                context.lineTo(10, parent.height);
                context.lineTo(50, 0);
                context.fillStyle = "#89C35C";
                context.fill();
            }
        }
    }

    RevoluteJoint {
        id: revoluteJoint
        bodyA: prop.body
        bodyB: lever.body
        localAnchorA: Qt.point(110,50)
        localAnchorB: Qt.point(50,0)
    }

    PhysicsItem {
        id: damper
        x: 650
        y: 260
        width: 110
        height: 20
        bodyType: Body.Dynamic
        fixtures: Box {
            width: damper.width
            height: damper.height
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
        bodyA: prop.body
        bodyB: damper.body
        localAnchorA: Qt.point(610,50)
        localAnchorB: Qt.point(0,-1)
        localAxisA: Qt.point(100,0)
        collideConnected: true
        enableLimit: true
        lowerTranslation: -110
        upperTranslation: 0
    }

    GearJoint {
        id: gearJoint
        bodyA: lever.body
        bodyB: damper.body
        joint1: revoluteJoint
        joint2: prismaticJoint
        ratio: 0.05
    }

    PhysicsItem {
        id: mixerLeft
        x: 90
        y: 500
        width: 10
        height: 50
        bodyType: Body.Dynamic
        fixtures: Box {
            width: mixerLeft.width
            height: mixerLeft.height
            density: 0.5
        }
        Rectangle {
            anchors.fill: parent
            color: "brown"
            antialiasing: true
        }
    }

    RevoluteJoint {
        id: mixerLeftJoint
        bodyA: leftWall.body
        bodyB: mixerLeft.body
        localAnchorA: Qt.point(100,500)
        localAnchorB: Qt.point(5,0)
    }

    PhysicsItem {
        id: mixerRight
        x: 710
        y: 500
        width: 10
        height: 50
        bodyType: Body.Dynamic
        fixtures: Box {
            width: mixerRight.width
            height: mixerRight.height
            density: 0.5
        }
        Rectangle {
            anchors.fill: parent
            color: "brown"
            antialiasing: true
        }
    }

    RevoluteJoint {
        id: mixerRightJoint
        bodyA: rightWall.body
        bodyB: mixerRight.body
        localAnchorA: Qt.point(-60,500)
        localAnchorB: Qt.point(5,0)
        enableMotor: true
        motorSpeed: 90
        maxMotorTorque: 10000
    }
    GearJoint {
        id: mixerJoint
        bodyA: mixerLeft.body
        bodyB: mixerRight.body
        joint1: mixerLeftJoint
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

    PhysicsItem {
        id: leftSensor
        x:40
        y: 360
        width: 360
        height:20
        fixtures: Box {
            width: leftSensor.width
            height: leftSensor.height
            sensor: true
            onBeginContact: {
                var target = other.getBody().target
                if (target.color === "#EFEFEF") {
                    target.color = "lightgreen"
                    leftCounter.count++;
                }
            }
        }
    }

    PhysicsItem {
        id: rightSensor
        x:400
        y: 360
        width: 360
        height:20
        fixtures: Box {
            width: rightSensor.width
            height: rightSensor.height
            sensor: true
            onBeginContact: {
                var target = other.getBody().target
                if (target.color === "#EFEFEF") {
                    target.color = "orange"
                    rightCounter.count++;
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
        world: physicsWorld
        opacity: 1
        visible: false
    }

    Timer {
        id: ballsTimer
        interval: 2000
        running: true
        repeat: true
        onTriggered: {
            var newBox = ballComponent.createObject(screen);
            newBox.x = 40 + (Math.random() * screen.width - 80);
            newBox.y = 50;
        }
    }
}
