import QtQuick 2.0
import Box2D 1.1

Item {
    id: screen
    width: 800
    height: 600
    World {
        id: world;
        anchors.fill: parent

        Repeater {
            model: 10
            delegate: Trapezoid {
                x: index * 150 + 10;
                y: Math.random() * (screen.height / 3);
                rotation: Math.random() * 90;
            }
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

        DebugDraw {
            world: world
            anchors.fill: world
            opacity: 0.75
        }
    }
}
