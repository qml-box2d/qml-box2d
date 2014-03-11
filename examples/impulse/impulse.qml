import QtQuick 2.0
import Box2D 1.1

Item {
    id: screen
    width: 800
    height: 600
    focus: true

    // BOX2D WORLD
    World {
	id: world;
	anchors.fill: parent

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

        Ball {
	    id: ball
	    x: parent.width /2
	    y: parent.height /2
	    rotation: 0
	    width: 100
	    height: 100
	}

	// Debug
	DebugDraw {
	    id: debugDraw
	    world: world
	    anchors.fill: world
	    opacity: 0.75
	    visible: false
	}

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ball.applyLinearImpulse(
                            Qt.point(10 * (mouseX - ball.x),
                                     10 * (mouseY - ball.y)),
                            Qt.point(ball.x, ball.y))
            }
        }
    }
}

