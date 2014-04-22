import QtQuick 2.2
import Box2D 1.1
import QtQuick.Controls 1.1

Rectangle {
    width: 800
    height: 600

    Component {
        id: ballComponent
        Body {
            id: ball
            width: 20
            height: 20
            sleepingAllowed: true
            bodyType: Body.Dynamic
            property bool burn: false
            function doDestroy() {
                destroy();
            }
            fixtures: Circle {
                property bool isBall: true
                anchors.fill: parent
                radius: 10
                density: 0.5
                friction: 1
                restitution: 0.2
            }
            Rectangle {
                id: ballShape
                border.color: "#999"
                color: "#DEDEDE"
                width: parent.width
                height: parent.height
                radius: 10
                SequentialAnimation {
                    running: ball.burn
                    PropertyAnimation {
                        target: ballShape
                        property: "color"
                        to: "red"
                        duration: 50
                    }
                    PropertyAnimation {
                        target: ballShape
                        property: "color"
                        to: "yellow"
                        duration: 50
                    }
                    PropertyAnimation {
                        target: ballShape
                        property: "opacity"
                        to: 0
                        duration: 50
                    }
                    onRunningChanged: {
                        if(!running)
                            ball.doDestroy();
                    }
                }
            }
        }
    }

    World {
        id: world
        anchors.fill: parent

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
            fixtures: Polygon {
                vertices: [
                    Qt.point(0,0),
                    Qt.point(parent.width,parent.height),
                    Qt.point(0,parent.height)

                ]
                anchors.fill: parent
                friction: 0.2
                density: 0.5
            }
            Canvas {
                id: groundCanvas
                anchors.fill: parent
                onPaint: {
                    var context = groundCanvas.getContext("2d");
                    context.beginPath();
                    context.moveTo(0,0);
                    context.lineTo(parent.width,parent.height);
                    context.lineTo(0,parent.height);
                    context.lineTo(0,0);
                    context.fillStyle = "#DEDEDE";
                    context.fill();
                }
            }
        }

        RayCast {
            id: sensorRay
            property point point1: Qt.point(40, 200)
            property point point2: Qt.point(fractionSlider.value * 10, 200)
            onFixtureReported: {
                if (fixture.isBall) {
                    intersectionPoint.x = point.x - 5;
                    intersectionPoint.y = point.y - 5;
                    intersectionPoint.opacity = 1;
                    pointHideAnimation.running = true;
                    bucketAnimation.to = point.x - 15;
                    bucketAnimation.running = true;
                }
            }
        }
        Connections {
            target: world
            onStepped: world.rayCast(sensorRay,
                                     sensorRay.point1,
                                     sensorRay.point2)
        }

        Rectangle {
            x: 40
            y: 200
            width: 10 * fractionSlider.value
            height: 1
            color: "aqua"
            opacity: 1
        }

        RayCast {
            id: laserRay
            onFixtureReported: fixture.parent.burn = true
            function cast() {
                world.rayCast(this, Qt.point(40, 300), Qt.point(700, 300))
            }
        }

        Rectangle {
            id: laser
            x: 40
            y: 300
            width: 700
            height: 1
            color: "red"
            opacity: 0
            PropertyAnimation {
                id: rayImpulseFadeoutAnimation
                target: laser
                property: "opacity"
                to: 0
                duration: 100
            }
        }

        Body {
            id: bucket
            x: 60
            y: 480
            height: 50
            width: 40
            bodyType: Body.Kinematic
            fixtures: [Polygon {
                    vertices: [
                        Qt.point(0,0),
                        Qt.point(40,0),
                        Qt.point(35,50),
                        Qt.point(5,50)
                    ]
                },
                Edge {
                    vertices: [
                        Qt.point(0,-1),
                        Qt.point(40,-1)
                    ]
                    sensor: true
                    onBeginContact: {
                        if(other.isBall)
                        {
                            other.parent.destroy();
                        }
                    }
                }
            ]
            Canvas {
                id:bucketCanvas
                anchors.fill: parent
                onPaint: {
                    var context = bucketCanvas.getContext("2d");
                    context.beginPath();
                    context.moveTo(0,0);
                    context.lineTo(40,0);
                    context.lineTo(35,50);
                    context.lineTo(5,50);
                    context.lineTo(0,0);
                    context.fillStyle = "lightblue";
                    context.fill();
                }
            }
            PropertyAnimation {
                id:bucketAnimation
                target: bucket
                property: "x"
                duration: 300
                easing.type: Easing.OutBack
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

        DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: world
            opacity: 0.7
            visible: false
        }
    }

    Slider {
        id: fractionSlider
        x: 180
        y: 10
        width: 200
        height: 30
        minimumValue: 1
        maximumValue: 70
        value: 70
    }

    Rectangle {
        id: intersectionPoint
        width: 10
        height: 10
        radius: 5
        color: "red"
        border.color: "yellow"
        opacity: 0
        PropertyAnimation {
            id: pointHideAnimation
            target: intersectionPoint
            property: "opacity"
            to: 0
            duration: 200
        }
    }

    Timer {
        id: rectTimer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            var newBall = ballComponent.createObject(world);
            newBall.x = 100 + (Math.random() * 600);
            newBall.y = 50;
        }
    }

    Timer {
        id: impulseTimer
        interval: 600
        running: true
        repeat: true
        onTriggered: {
            laserRay.cast();
            laser.opacity = 1;
            rayImpulseFadeoutAnimation.running = true;
        }
    }
}
