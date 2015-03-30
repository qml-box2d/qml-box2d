import QtQuick 2.2
import Box2D 2.0
import QtQuick.Controls 1.1
import "../shared"

Rectangle {
    width: 800
    height: 600

    Component {
        id: ballComponent
        PhysicsItem {
            id: ball
            width: 20
            height: 20
            bodyType: Body.Dynamic

            fixtures: Circle {
                property bool isBall: true
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
            }
        }
    }

    World {
        id: physicsWorld

        onStepped:
            physicsWorld.rayCast(sensorRay,
                                 sensorRay.point1,
                                 sensorRay.point2)
    }

    Item {
        id: physicsRoot
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

        PhysicsItem {
            id: ground
            height: 40
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            fixtures: Polygon {
                vertices: [
                    Qt.point(0,0),
                    Qt.point(ground.width,ground.height),
                    Qt.point(0,ground.height)

                ]
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

        Rectangle {
            x: 40
            y: 200
            width: 10 * fractionSlider.value
            height: 1
            color: "aqua"
            opacity: 1
        }

        PhysicsItem {
            id: bucket
            x: 60
            y: 480
            height: 50
            width: 40
            bodyType: Body.Kinematic
            fixtures: [
                Polygon {
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
                        if (other.isBall)
                            other.getBody().target.destroy();
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
            var newBall = ballComponent.createObject(physicsRoot);
            newBall.x = 100 + (Math.random() * 600);
            newBall.y = 50;
        }
    }
}
