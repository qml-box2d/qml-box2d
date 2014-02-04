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
            height: 20
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

    Text {
        width: parent.width
        y:50
        text: "Fixtures tests"
        height: 30
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter

    }

    World {
        id: world
        anchors.fill: parent

        Body {
            function getVertices() {
                var pos = 40;
                var arr = [];
                arr.push(Qt.point(0,0));
                arr.push(Qt.point(40,0));
                while(pos < 700) {
                    var y = Math.round(Math.random() * 30);
                    var x = Math.round(20 + Math.random() * 40);
                    pos += x;
                    arr.push(Qt.point(pos,y));
                }
                arr.push(Qt.point(760,0));
                arr.push(Qt.point(800,0));
                arr.push(Qt.point(800,40));
                arr.push(Qt.point(0,40));
                return arr;
            }
            height: 40
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            z: 100
            id: ground
            bodyType: Body.Static
            fixtures: Chain {
                id: groundShape
                vertices: ground.getVertices()
                anchors.fill: parent
                loop: true
            }
            Canvas {
                id: groundCanvas
                anchors.fill: parent
                onPaint: {
                    var context = groundCanvas.getContext("2d");
                    context.beginPath();
                    context.moveTo(0,0);
                    var points = groundShape.vertices;
                    for(var i = 1;i < points.length;i ++) {
                        var point = points[i];
                        var x = point.x;
                        var y = point.y;
                        context.lineTo(x,y);
                    }
                    context.fillStyle = "#000000";
                    context.fill();

                }
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
            id: dynamicTest
            bodyType: Body.Static
            x: 200
            y: 150
            width: 200
            height: 30
            fixtures: [
                Box {
                    x: 0
                    y: 0
                    width: parent.width * 0.45
                    height: parent.height
                },
                Box {
                    x: parent.width * 0.55
                    y: 0
                    width: parent.width * 0.45
                    height: parent.height

                }
            ]
            Rectangle {
                anchors.fill: parent
                color: "blue"
            }

        }

        Body {
            id: staticTest
            bodyType: Body.Static
            x: 350
            y: 250
            width: 100
            height: 25
            fixtures: Box {
                x: 0
                y: 0
                width: 100
                height: 25
            }
            Rectangle {
                anchors.fill: parent
                color: "orange"
            }
        }

        Body {
            id: radiusTest
            bodyType: Body.Dynamic
            x: 600
            y: 100
            width: 100
            height: 100
            fixtures:
                Circle {
                radius: parent.width / 2
                anchors.centerIn: parent
                density: 0.9
                friction: 0.3
                restitution: 0.8
            }
            Rectangle {
                anchors.centerIn: parent
                radius: parent.width / 2
                width: parent.width
                height: parent.height
                color: "red"
            }
        }

        Body {
            id: polygonTest
            bodyType: Body.Dynamic
            x: 450
            y: 50
            width: 100
            height: 100
            fixtures:
                Polygon {
                width: parent.width
                height: parent.height
                vertices: [
                    Qt.point(width / 2,0),
                    Qt.point(width,height),
                    Qt.point(0,height)
                ]
                density: 0.9
                friction: 0.3
                restitution: 0.8
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

        Rectangle {
            id: ballsButton
            x: 50
            y: 100
            width: 120
            height: 30
            Text {
                text: "Falling balls"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ballsTimer.running = !ballsTimer.running;
                }
            }
        }

        Text {
            id: ballsCounter
            x: 200
            y: 100
            height: 30
            width: 50
            font.pixelSize: 13
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            property int count: 0
            text: count + " balls"
        }

        Timer {
            id: ballsTimer
            interval: 200
            running: false
            repeat: true
            onTriggered: {
                var newBox = ballComponent.createObject(world);
                newBox.x = 40 + (Math.random() * world.width - 80);
                newBox.y = 50;
                ballsCounter.count ++;
            }
        }

        Rectangle {
            id: dynamicTestButton
            x: 50
            y: 140
            width: 120
            height: 30
            Text {
                text: "Dynamic fixtures"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(dynamicTest.width == 300)
                    {
                        dynamicTest.width = 200
                        dynamicTest.height = 30
                    }
                    else
                    {
                        dynamicTest.width = 300
                        dynamicTest.height = 50
                    }
                }
            }

        }

        Rectangle {
            id: staticTestButton
            x: 50
            y: 180
            width: 120
            height: 30
            Text {
                text: "Static fixture"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(staticTest.width == 200)
                    {
                        staticTest.width = 100
                        staticTest.height = 25
                    }
                    else
                    {
                        staticTest.width = 200
                        staticTest.height = 50
                    }
                }
            }

        }
        Rectangle {
            id: radiusTestButton
            x: 50
            y: 220
            width: 120
            height: 30
            Text {
                text: "Circle"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(radiusTest.width == 150)
                    {
                        radiusTest.width = 100
                        radiusTest.height = 100
                    }
                    else
                    {
                        radiusTest.width = 150
                        radiusTest.height = 150
                    }
                }
            }
        }

        Rectangle {
            id: polygonTestButton
            x: 50
            y: 260
            width: 120
            height: 30
            Text {
                text: "Polygon"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(polygonTest.height == 100 && polygonTest.width == 100)
                        polygonTest.height = 200;
                    else if(polygonTest.height == 200 && polygonTest.width == 100)
                        polygonTest.width = 200;
                    else
                    {
                        polygonTest.height = 100;
                        polygonTest.width = 100;
                    }
                }
            }
        }

        Rectangle {
            id: chainTestButton
            x: 50
            y: 300
            width: 120
            height: 30
            Text {
                text: "Chain"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(ground.height == 40)
                        ground.height = 100
                    else
                        ground.height = 40
                }
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

        DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: world
            opacity: 1
            visible: true
        }
    }
}
