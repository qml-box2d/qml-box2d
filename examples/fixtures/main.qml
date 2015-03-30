import QtQuick 2.2
import Box2D 2.0
import "../shared"

Rectangle {
    id: screen

    width: 800
    height: 600

    Component {
        id: ballComponent
        Rectangle {
            id: ball

            width: 20
            height: 20
            radius: 10
            border.color: "blue"
            color: "#EFEFEF"

            CircleBody {
                target: ball
                world: physicsWorld

                bodyType: Body.Dynamic

                radius: ball.width / 2
                density: 0.1
                friction: 0.3
                restitution: 0.5
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

    World { id: physicsWorld }

    PhysicsItem {
        function getVertices(height) {
            var pos = height;
            var arr = [];
            arr.push(Qt.point(0,0));
            arr.push(Qt.point(height,0));
            while (pos < 700) {
                var y = Math.round(Math.random() * height);
                var x = Math.round(20 + Math.random() * 40);
                pos += x;
                arr.push(Qt.point(pos,y));
            }
            arr.push(Qt.point(760,0));
            arr.push(Qt.point(800,0));
            arr.push(Qt.point(800,height));
            arr.push(Qt.point(0,height));
            return arr;
        }
        height: 40
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        z: 100
        id: ground
        fixtures: Chain {
            id: groundShape
            vertices: ground.getVertices(ground.height)
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
                for (var i = 1; i < points.length; i++) {
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

    PhysicsItem {
        id: dynamicTest
        x: 200
        y: 150
        width: 200
        height: 30
        fixtures: [
            Box {
                x: 0
                y: 0
                width: dynamicTest.width * 0.45
                height: dynamicTest.height
            },
            Box {
                x: dynamicTest.width * 0.55
                y: 0
                width: dynamicTest.width * 0.45
                height: dynamicTest.height
            }
        ]
        Rectangle {
            anchors.fill: parent
            color: "blue"
        }
    }

    PhysicsItem {
        id: staticTest
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

    PhysicsItem {
        id: radiusTest
        bodyType: Body.Dynamic
        x: 600
        y: 100
        fixtures: [
            Circle {
                id: circleShape
                radius: 50
                x: -circleShape.radius
                y: -circleShape.radius
                density: 0.9
                friction: 0.3
                restitution: 0.8
            }
        ]
        Rectangle {
            width: circleShape.radius * 2
            height: circleShape.radius * 2
            anchors.centerIn: parent
            radius: circleShape.radius
            color: "red"
        }
    }

    PhysicsItem {
        id: polygonTest
        world: physicsWorld
        bodyType: Body.Dynamic
        x: 450
        y: 50
        width: 100
        height: 100
        fixtures: Polygon {
            vertices: [
                Qt.point(polygonTest.width / 2,0),
                Qt.point(polygonTest.width,polygonTest.height),
                Qt.point(0,polygonTest.height)
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
            var newBox = ballComponent.createObject(screen);
            newBox.x = 40 + (Math.random() * screen.width - 80);
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
                if (circleShape.radius == 75)
                    circleShape.radius = 50
                else
                    circleShape.radius = 75
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
                if (ground.height == 40)
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
            text: debugDraw.visible ? "Debug view: on" : "Debug view: off"
            anchors.centerIn: parent
        }
        color: "#DEDEDE"
        border.color: "#999"
        radius: 5
        MouseArea {
            anchors.fill: parent
            onClicked: debugDraw.visible = !debugDraw.visible
        }
    }

    DebugDraw {
        id: debugDraw
        anchors.fill: parent
        world: physicsWorld
        opacity: 1
        visible: false
    }
}
