import QtQuick 2.2
import Box2D 2.0
import "../shared"

Rectangle {
    width: 800
    height: 600

    property Body pressedBody: null

    function randomColor() {
        return Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
    }

    MouseJoint {
        id: mouseJoint
        bodyA: anchor
        dampingRatio: 0.8
        maxForce: 100
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onPressed: {
            if (pressedBody != null) {
                mouseJoint.maxForce = pressedBody.getMass() * 500;
                mouseJoint.target = Qt.point(mouseX, mouseY);
                mouseJoint.bodyB = pressedBody;
            }
        }

        onPositionChanged: {
            mouseJoint.target = Qt.point(mouseX, mouseY);
        }

        onReleased: {
            mouseJoint.bodyB = null;
            pressedBody = null;
        }
    }

    World { id: physicsWorld }

    RectangleBoxBody {
        id: ground
        color: "#DEDEDE"
        height: 40
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        world: physicsWorld
        friction: 1
        density: 1
    }

    Wall {
        id: topWall
        height: 40
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
    }

    Wall {
        id: leftWall
        width: 40
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 40
        }
    }

    Wall {
        id: rightWall
        width: 40
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 40
        }
    }

    Body {
        id: anchor
        world: physicsWorld
    }

    Repeater {
        model: 20
        Rectangle {
            id: rectangle

            x: 40 + Math.random() * 720
            y: 40 + Math.random() * 520
            width: 20 + Math.random() * 100
            height: 20 + Math.random() * 100
            rotation: Math.random() * 360
            color: randomColor()
            border.color: randomColor()
            smooth: true

            Body {
                id: rectangleBody

                target: rectangle
                world: physicsWorld
                bodyType: Body.Dynamic

                Box {
                    width: rectangle.width
                    height: rectangle.height
                    density: 0.5
                    restitution: 0.5
                    friction: 0.5
                }
            }

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                onPressed: {
                    mouse.accepted = false;
                    pressedBody = rectangleBody;
                }
            }
        }
    }

    Rectangle {
        id: debugButton
        x: 50
        y: 50
        width: 120
        height: 30
        Text {
            text: debugDraw.visible ? "Debug view: on" : "Debug view: off"
            anchors.centerIn: parent
        }
        color: "#DEDEDE"
        border.color: "#999"
        radius: 5
        MouseArea {
            anchors.fill: parent
            onClicked: debugDraw.visible = !debugDraw.visible;
        }
    }

    DebugDraw {
        id: debugDraw
        world: physicsWorld
        opacity: 0.75
        visible: false
    }
}
