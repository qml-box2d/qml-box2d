import QtQuick 2.2
import QtQuick.Window 2.0
import QtQuick.Controls 1.1

import Box2D 2.0
import Box2D.Components 1.0



Window{
    visible: true
    title: qsTr("Wheel Example")
    width: 800
    height: 600
    Rectangle {
        id: screen
        anchors.fill: parent
        color: "#EFEFFF"

        Component {
            id: ballsComponent
            PhysicsItem {
                id: ball
                width: 20
                height: 20
                bodyType: Body.Dynamic
                property color boxColor: "blue"
                fixtures: Circle {
                    id: fx
                    radius: ball.width / 2
                    density: 0.1
                    friction: 1
                    restitution: 0.5
                }
                Rectangle {
                    radius: parent.width / 2
                    border.color: "blue"
                    color: "#EFEFEF"
                    width: parent.width
                    height: parent.height
                    smooth: true
                }
            }
        }
        World { id: physicsWorld }

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

        PhysicsItem {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            anchors.rightMargin: 40
            width: 300
            height: 300
            fixtures: Chain {
                vertices: [
                    Qt.point(0,300),
                    Qt.point(210,180),
                    Qt.point(240,130),
                    Qt.point(240,50),
                    Qt.point(220,0),
                    Qt.point(300,0),
                    Qt.point(300,300)
                ]
            }
            Canvas {
                id: canvas1
                anchors.fill: parent
                onPaint: {
                    var context = canvas1.getContext("2d");
                    context.beginPath();
                    context.moveTo(0,300);
                    context.lineTo(210,180);
                    context.lineTo(240,130);
                    context.lineTo(240,50);
                    context.lineTo(220,0);
                    context.lineTo(300,0);
                    context.lineTo(300,300);
                    context.fillStyle = "#AAA";
                    context.fill();
                }
            }
        }

        Wall {
            anchors.right: parent.right
            anchors.rightMargin: 40
            width:500
            height: 40
            y: 220
        }

        PhysicsItem {
            id: body
            property int speed: speedSlider.value
            property int k: -1
            x: 600
            y: 100
            width: 100
            height: 20
            bodyType: Body.Dynamic
            fixtures: Box {
                width: body.width
                height: body.height
                density: 0.8
                friction: 0.5
                restitution: 0.8
            }
            Rectangle {
                anchors.fill: parent
                color: "orange"
            }
        }
        PhysicsItem {
            id: wheelA
            x: 700
            y: 100
            width: 48
            height: 48
            bodyType: Body.Dynamic
            fixtures: Circle {
                radius: wheelA.width / 2
                density: 0.8
                friction: 10
                restitution: 0.8
            }
            Image {
                source: "qrc:/images/wheel.png"
                anchors.fill: parent
            }
        }

        PhysicsItem {
            id: wheelB
            x: 600
            y: 100
            width: 48
            height: 48
            bodyType: Body.Dynamic
            fixtures: Circle {
                radius: wheelB.width / 2
                density: 0.8
                friction: 10
                restitution: 0.8
            }
            Image {
                source: "qrc:/images/wheel.png"
                anchors.fill: parent
            }
        }

        WheelJoint {
            id: wheelJointA
            bodyA: body.body
            bodyB: wheelA.body
            localAnchorA: Qt.point(100,10)
            localAnchorB: Qt.point(24,24)
            enableMotor: true
            motorSpeed: body.k * body.speed
            maxMotorTorque: torqueSlider.value
            frequencyHz: 10
        }

        WheelJoint {
            id: wheelJointB
            bodyA: body.body
            bodyB: wheelB.body
            localAnchorA: Qt.point(0,10)
            localAnchorB: Qt.point(24,24)
            enableMotor: true
            motorSpeed: body.k * body.speed
            maxMotorTorque: torqueSlider.value
            frequencyHz: 10
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
        Text {
            id: leftMotorState
            x: 180
            y: 50
            width: 200
            text : "Speed: " + speedSlider.value +
                   "\nTorque: " + torqueSlider.value
        }

        Slider {
            id: speedSlider
            x: 50
            y: 90
            width: 120
            height: 20
            minimumValue: 0
            maximumValue: 720
            value: 0
            stepSize: 1
        }
        Slider {
            id: torqueSlider
            x: 50
            y: 120
            width: 120
            height: 20
            minimumValue: 1
            maximumValue: 100
            value: 50
            stepSize: 1
        }
        Rectangle {
            id: leftButton
            x: 50
            y: 150
            width: 30
            height: 30
            color: body.k > 0 ? "#FFF" : "#DEDEDE"
            border.color: "#999"
            radius: 5
            Image {
                width: 24
                height: 24
                anchors.centerIn: parent
                source: "qrc:/images/arrow.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        body.k = -1
                    }
                }
            }
        }
        Rectangle {
            id: rightButton
            x: 90
            y: 150
            width: 30
            height: 30
            color: body.k < 0 ? "#FFF" : "#DEDEDE"
            border.color: "#999"
            radius: 5
            Image {
                width: 24
                height: 24
                anchors.centerIn: parent
                source: "qrc:/images/arrow.png"
                rotation: 180
                MouseArea {
                    anchors.fill: parent
                    onClicked: body.k = 1
                }
            }
        }

        DebugDraw {
            id: debugDraw
            world: physicsWorld
            opacity: 0.5
            z: 1
            visible: false
        }

        Timer {
            id: ballsTimer
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                var newBox = ballsComponent.createObject(screen);
                newBox.x = 40 + Math.round(Math.random() * 720);
                newBox.y = 50;
            }
        }
    }
}
