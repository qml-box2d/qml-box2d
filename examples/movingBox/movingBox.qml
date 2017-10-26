import QtQuick 2.0
import Box2D 2.0
import "../shared"

Item {
    id: screen
    width: 800
    height: 600
    focus: true

    Keys.onPressed: {
        if (event.key === Qt.Key_Left) {
            movableBox.moveBackward();
            event.accepted = true;
        }
        else if (event.key === Qt.Key_Right) {
            movableBox.moveForward();
            event.accepted = true;
        }
        else if (event.key === Qt.Key_Up) {
            movableBox.jump();
            event.accepted = true;
        }
        event.accepted = true;
    }

    Keys.onReleased: {
        if (event.isAutoRepeat)
            return ;

        if (event.key === Qt.Key_Left ||
            event.key === Qt.Key_Right) {
            movableBox.stopMoving();
        }
    }

    Text {
        anchors {
            right: parent.right
            top: parent.top
            left: parent.left
        }
        height: 40
        horizontalAlignment: Text.AlignHCenter;
        text: "Left/Right key to control the direction, Up key to jump."
    }

    World { id: physicsWorld; }

    Repeater {
        model: 4
        delegate: WoodenBox {
            x: Math.random() * (screen.width - 100);
            y: Math.random() * (screen.height / 3);
            rotation: Math.random() * 90;
        }
    }

    MovableBox {
        id: movableBox
        width: 40
        height: width
    }

    ScreenBoundaries {}
}
