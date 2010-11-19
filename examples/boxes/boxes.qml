import Qt 4.7
import Box2D 2.0
import QtMobility.sensors 1.1

Image {
    id: screen;
    width: 640;
    height: 480;

    source: "background.png"

    World {
        id: world;
        anchors.fill: parent

        WoodenBox {
            x: 20; y: 20;
            rotation: 46;
        }
        WoodenBox {
            x: 200; y: 30;
            rotation: -33;
        }
        WoodenBox {
            x: 300; y: 150;
            rotation: -5;
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
    }

    Accelerometer  {
        Component.onCompleted: start()
        onReadingChanged: {
            var r = reading
            world.gravity = Qt.point(-r.y * 0.1, r.x * 0.1)
        }
    }
}
