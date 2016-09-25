import QtQuick 2.0
import QtQuick.Window 2.0
import Box2D 2.0
import Box2D.Components 1.0


Window{
    visible: true
    title: qsTr("Moving Box Example")
    width: 800
    height: 600

    Item {
        id: screen
        anchors.fill: parent
        focus: true

        Keys.onPressed: {
            if (event.key === Qt.Key_Left) {
                movableBox.moveBackward();
            }
            else if (event.key === Qt.Key_Right) {
                movableBox.moveForward();
            }
            else if (event.key === Qt.Key_Up) {
                movableBox.jump();
            }
        }

        Keys.onReleased: {
            if (event.isAutoRepeat)
                return ;

            if (event.key === Qt.Key_Left ||
                    event.key === Qt.Key_Right) {
                movableBox.stopMoving();
            }
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
}
