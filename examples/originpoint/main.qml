import QtQuick 2.2
import Box2D 1.1

Rectangle {
    width: 800
    height: 600
    color: "#555"

    World {
        id: world
        anchors.fill: parent

        Body {
            id: bodyBox
            x: 50
            y: 200
            width: 200
            height: 60
            bodyType: Body.Kinematic
            originPoint: Qt.point(100,30)
            angularVelocity: 90
            fixtures: Box {
                anchors.fill: parent
            }
            Rectangle {
                anchors.fill: parent
                color: "yellow"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    bodyBox.originPoint = Qt.point(mouse.x,mouse.y);
                }
            }
        }

        Body {
            id: bodyCircle
            x: 300
            y: 200
            width: 100
            height: 100
            bodyType: Body.Kinematic
            originPoint: Qt.point(30,30)
            angularVelocity: -90
            fixtures: Circle {
                anchors.fill: parent
                radius: 50
            }
            Rectangle {
                anchors.fill: parent
                radius: 50
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "blue" }
                    GradientStop { position: 0.75; color: "magenta" }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    bodyCircle.originPoint = Qt.point(mouse.x,mouse.y);
                }
            }
        }

        Body {
            id: bodyPolygon
            x: 450
            y: 200
            width: 100
            height: 100
            bodyType: Body.Kinematic
            originPoint: Qt.point(50,20)
            angularVelocity: 180
            fixtures: Polygon {
                anchors.fill: parent
                vertices: [
                    Qt.point(50,0),
                    Qt.point(0,100),
                    Qt.point(100,100)
                ]
            }
            Canvas {
                id: bodyPolygonCanvas;
                anchors.fill: parent
                onPaint: {
                    var context = bodyPolygonCanvas.getContext("2d");
                    context.beginPath();
                    context.moveTo(50,0);
                    context.lineTo(0,100);
                    context.lineTo(100,100);
                    context.lineTo(50,0);
                    context.fillStyle = "green";
                    context.fill();
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    bodyPolygon.originPoint = Qt.point(mouse.x,mouse.y);
                }
            }
        }

        Body {
            id: bodyChain
            x: 650
            y: 200
            width: 80
            height: 200
            bodyType: Body.Kinematic
            originPoint: Qt.point(40,100)
            angularVelocity: -45
            fixtures: Chain {
                anchors.fill: parent
                vertices: [
                    Qt.point(0,0),
                    Qt.point(20,100),
                    Qt.point(0,200),
                    Qt.point(80,200),
                    Qt.point(60,100),
                    Qt.point(80,0)
                ]
                loop: true
            }
            Canvas {
                id: bodyChainCanvas;
                anchors.fill: parent
                onPaint: {
                    var context = bodyChainCanvas.getContext("2d");
                    context.beginPath();
                    context.moveTo(0,0);
                    context.lineTo(20,100);
                    context.lineTo(0,200);
                    context.lineTo(80,200);
                    context.lineTo(60,100);
                    context.lineTo(80,0);
                    context.lineTo(0,0);
                    context.strokeStyle = "orange";
                    context.stroke();
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    bodyChain.originPoint = Qt.point(mouse.x,mouse.y);
                }
            }
        }

        Body {
            x: 690
            y: 240
            width: 20
            height: 20
            bodyType: Body.Dynamic
            fixtures: Circle {
                anchors.fill: parent
                radius: 10
                density: 0.5
                restitution: 0.8
            }
            Rectangle {
                anchors.fill: parent
                radius: 10
                color: "aqua"
            }
        }

        Rectangle {
            id: debugButton
            x: 10
            y: 10
            width: 120
            height: 30
            Text {
                id: debugButtonText
                text: "Debug view: on"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    debugDraw.visible = !debugDraw.visible
                    debugButtonText.text = debugDraw.visible ? "Debug view: on" : "Debug view: off"
                }
            }
        }

        Rectangle {
            id: centerButton
            x: 140
            y: 10
            width: 120
            height: 30
            Text {
                text: "All to center"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    bodyBox.transformOrigin = Item.Center;
                    bodyCircle.transformOrigin = Item.Center;
                    bodyPolygon.transformOrigin = Item.Center;
                    bodyChain.transformOrigin = Item.Center;
                }
            }
        }

        Rectangle {
            id: randomButton
            x: 270
            y: 10
            width: 120
            height: 30
            Text {
                text: "All to random"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    bodyBox.originPoint = Qt.point(Math.random() * 100,Math.random() * 100);
                    bodyCircle.originPoint = Qt.point(Math.random() * 100,Math.random() * 100);
                    bodyPolygon.originPoint = Qt.point(Math.random() * 100,Math.random() * 100);
                    bodyChain.originPoint = Qt.point(Math.random() * 100,Math.random() * 100);
                }
            }
        }

        DebugDraw {
            id: debugDraw
            world: world
            anchors.fill: parent
            opacity: 0.6
            visible: true
        }
    }
}
