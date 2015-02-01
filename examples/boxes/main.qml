import QtQuick 2.0
import Box2D 2.0

Image {
    id: screen
    width: 640
    height: 480

    source: "background.png"

    World { id: physicsWorld }

    Repeater {
        model: 3
        delegate: WoodenBox {
            x: Math.random() * (screen.width - 100)
            y: Math.random() * (screen.height / 3)
            rotation: Math.random() * 90
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
        id: debugDraw
        world: physicsWorld
        anchors.fill: parent
        opacity: 0.75
        visible: false
    }

    MouseArea {
        id: debugMouseArea
        anchors.fill: parent
        onPressed: debugDraw.visible = !debugDraw.visible
    }
}
