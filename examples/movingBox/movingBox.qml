import QtQuick 2.0
import Box2D 1.1

Item {
    id: screen
    width: 800
    height: 600
    focus: true
    Keys.onPressed: onKeysPressed(event)
    Keys.onReleased: onKeysReleased(event)

    function onKeysPressed(event) {
        if (event.key == Qt.Key_Left) {
            movableBox.moveBackward();
        }
        else if (event.key == Qt.Key_Right) {
            movableBox.moveForward();
        }
        else if (event.key == Qt.Key_Up) {
            movableBox.jump();
        }
    }

    function onKeysReleased(event) {
        if (event.isAutoRepeat)
            return ;

        if (event.key == Qt.Key_Left ||
            event.key == Qt.Key_Right) {
            movableBox.stopMoving();
        }
    }

    World {
        id: world;
        anchors.fill: parent

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

        Wall {
            id: ground
            height: 20
            anchors { left: parent.left; right: parent.right; top: parent.bottom }
        }
        Wall {
            id: ceiling
            height: 20
            anchors { left: parent.left; right: parent.right; bottom: parent.top }
        }
        Wall {
            id: leftWall
            width: 20
            anchors { right: parent.left; bottom: ground.top; top: ceiling.bottom }
        }
        Wall {
            id: rightWall
            width: 20
            anchors { left: parent.right; bottom: ground.top; top: ceiling.bottom }
        }
    }
}
