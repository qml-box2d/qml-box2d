import Qt 4.7
import Box2D 1.0

Rectangle {
    id: screen;
    width: 640;
    height: 480;
    color: "lightblue"

    // A heavy ball that will be created dynamically with the timer below
    Component {
        id: heavyBall
        Body {
            fixtures: Circle {
                radius: 40
                density: 5
                friction: 0.3
                restitution: 0.2
            }

            Rectangle {
                anchors.centerIn: parent
                radius: 40
                width: 80
                height: 80
                smooth: true
                color: Qt.rgba(0.2, 0.2, 0.2, 1)
                border.color: Qt.rgba(0.1, 0.1, 0.1, 1)
            }
        }
    }

    // Timer that keeps creating heavy balls that crash down on the building
    Timer {
        running: true
        repeat: true
        interval: 1000
        onTriggered: {
            var ball = heavyBall.createObject(world)
            ball.x =  Math.random() * world.width
            ball.y = -100
        }
    }

    World {
        id: world;
        anchors.fill: parent

        Building {
            id: victim
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            floors: 8
            stairways: 30
        }

        Wall {
            id: ground
            height: 200
            anchors { left: parent.left; right: parent.right; top: parent.bottom }
        }

        DebugDraw {
            id: debugDraw
            world: world
            anchors.fill: world
            opacity: 0.75
            visible: false
            z: 1
        }
        MouseArea {
            id: debugMouseArea
            anchors.fill: world
            onPressed: debugDraw.visible = !debugDraw.visible
        }
    }
}
