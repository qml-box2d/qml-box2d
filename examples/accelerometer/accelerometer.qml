import Qt 4.7
import Box2D 1.0
import QtMobility.sensors 1.1

Image {
    id: screen;
    width: 640;
    height: 480;

    source: "background.png"

    World {
        id: world;
        anchors.fill: parent

        Repeater {
            model: 3
            delegate: WoodenBox {
                x: Math.random() * (screen.width - 100);
                y: Math.random() * (screen.height / 3);
                rotation: Math.random() * 90;
            }
        }

        Body {
            id: ground
            height: 20
            anchors { left: parent.left; right: parent.right; top: parent.bottom }
            bodyType: Body.Static
        }
        Body {
            id: ceiling
            height: 20
            anchors { left: parent.left; right: parent.right; bottom: parent.top }
            bodyType: Body.Static
        }
        Body {
            id: leftWall
            width: 20
            anchors { right: parent.left; bottom: ground.top; top: ceiling.bottom }
            bodyType: Body.Static
        }
        Body {
            id: rightWall
            width: 20
            anchors { left: parent.right; bottom: ground.top; top: ceiling.bottom }
            bodyType: Body.Static
        }

        DebugDraw {
            id: debugDraw
            world: world
            anchors.fill: world
            opacity: 0.75
            visible: false
        }
        MouseArea {
            id: debugMouseArea
            anchors.fill: world
            onPressed: debugDraw.visible = !debugDraw.visible
        }
    }

    Accelerometer  {
        Component.onCompleted: start()
        onReadingChanged: {
            var r = reading
            world.gravity = Qt.point(-r.y * 0.1, r.x * 0.1)
        }
    }
}
