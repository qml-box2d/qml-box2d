import QtQuick 2.0
import Box2D 2.0
import QtSensors 5.0
import "../shared"

Image {
    id: screen

    width: 640
    height: 480

    source: "background.png"

    World { id: physicsWorld }

    Repeater {
        model: 3
        delegate: WoodenBox {
            x: Math.random() * (screen.width - 100);
            y: Math.random() * (screen.height / 3);
            rotation: Math.random() * 90;
        }
    }

    ScreenBoundaries {}

    DebugDraw {
        id: debugDraw
        world: physicsWorld
        opacity: 0.75
        visible: false
    }
    MouseArea {
        id: debugMouseArea
        anchors.fill: screen
        onPressed: debugDraw.visible = !debugDraw.visible
    }

    Accelerometer {
        Component.onCompleted: start()
        onReadingChanged: {
            var r = reading;
            physicsWorld.gravity = Qt.point(r.x, r.y);
        }
    }
}
