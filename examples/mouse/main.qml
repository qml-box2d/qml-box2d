import QtQuick 2.2
import Box2D 1.1


Rectangle {
    width: 800
    height: 600

    function randomColor() {
        return Qt.rgba(Math.random(), Math.random(), Math.random(), Math.random());
    }

    MouseJoint {
        id: mouseJoint
        bodyA: anchor
        dampingRatio: 0.8
        target: Qt.point(mouseArea.mouseX,
                         mouseArea.mouseY);
        maxForce: 100
    }

    MouseArea {
        id: mouseArea
        onReleased: mouseJoint.bodyB = null
        anchors.fill: parent
        hoverEnabled: true
    }

    World {
        id: world
        anchors.fill: parent

        Body {
            id: ground
            height: 40
            bodyType: Body.Static
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            fixtures: Box {
                anchors.fill: parent
                friction: 1
                density: 1
            }
            Rectangle {
                anchors.fill: parent
                color: "#DEDEDE"
            }
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
            x:300
            y: 300
            width: 10
            height: 10
        }
        Repeater {
            model: 20
            Body {
                x: 40 + Math.random() * 720
                y: 40 + Math.random() * 520
                width: 20 + Math.random() * 100
                height: 20 + Math.random() * 100
                bodyType: Body.Dynamic
                rotation: Math.random() * 360
                fixtures: Box {
                    anchors.fill: parent
                    density: 0.5
                    restitution: 0.5
                    friction: 0.5
                }
                Rectangle {
                    anchors.fill: parent
                    color: randomColor()
                    border.color: randomColor()
                    smooth: true
                }
                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true
                    onPressed: {
                        mouseJoint.maxForce = parent.getMass() * 500;
                        mouseJoint.bodyB = parent
                        mouse.accepted = false
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
                id: debugButtonText
                text: "Debug view: off"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    debugDraw.visible = !debugDraw.visible;
                    debugButtonText.text = debugDraw.visible ? "Debug view: on" : "Debug view: off";
                }
            }
        }

        DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: world
            opacity: 1
            visible: false
        }
    }
}
