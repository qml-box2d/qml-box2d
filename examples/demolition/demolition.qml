import QtQuick 2.0
import Box2D 2.0
import "../shared"

Image {
    id: screen;
    width: 640; height: 360
    source: "images/background.png"
    Image {
        id: skyline
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        source: "images/skyline.png"
    }

    // A wheel that will be created dynamically
    Component {
        id: wheelComponent
        Image {
            id: wheel

            smooth: true
            source: "images/wheel.png"

            CircleBody {
                id: wheelBody

                world: physicsWorld
                target: wheel
                bodyType: Body.Dynamic

                density: 6
                friction: 1.0
                restitution: 0.6

                radius: wheel.width / 2
            }

            MouseArea {
                anchors.fill: parent
                onReleased: timer.running = false
                onPressed: {
                    if(wheel.x < (physicsRoot.width / 2)) {
                        timer.clockwise = true
                    }
                    else {
                        timer.clockwise = false
                    }

                    timer.running = true
                }

                Timer {
                    id: timer
                    property bool clockwise
                    interval: 100
                    repeat: true
                    onTriggered: {
                        if(clockwise) {
                            wheelBody.applyTorque(-3000)
                        }
                        else {
                            wheelBody.applyTorque(3000)
                        }
                    }
                }
            }
        }
    }

    Text {
        anchors {
            top: parent.top; topMargin: 20
            left: parent.left; leftMargin: 25
        }

        text: "Press and hold to create a wheel.\nPress and hold on top of the wheel to apply torque."
        color: "white"
        font.pixelSize: 12
    }

    Flickable {
        anchors.fill: parent

        // Try to double the contentWidth..
        contentWidth: physicsRoot.width // * 2
        contentHeight: physicsRoot.height

        World { id: physicsWorld }

        Item {
            id: physicsRoot
            width: screen.width
            height: screen.height

            MouseArea {
                anchors.fill: parent
                onPressAndHold: {
                    var wheel = wheelComponent.createObject(physicsRoot)
                    wheel.x = mouse.x - wheel.width / 2
                    wheel.y = mouse.y - wheel.height / 2
                }
            }

            Building {
                id: victim
                anchors {
                    bottom: ground.top
                }
                x: 100
                floors: 6
                stairways: 3
            }

            Building {
                anchors {
                    bottom: ground.top
                }
                x: 400
                floors: 6
                stairways: 3
            }

            Wall {
                id: ceiling
                height: 20
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
            }

            Wall {
                id: leftWall
                width: 20
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                }
            }

            Wall {
                id: rightWall
                width: 20
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                }
            }

            Wall {
                id: ground
                height: 20
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
            }

            Wall {
                id: exitWall
                width: 85
                height: 20
                anchors {
                    top: ceiling.bottom
                    right: rightWall.left
                }
            }
        }

        DebugDraw {
            id: debugDraw
            anchors.fill: physicsRoot
            world: world
            opacity: 0.75
            visible: false
        }
    }


    Image {
        anchors {
            top: parent.top; topMargin: 10
            right: parent.right; rightMargin: 20
        }

        fillMode: Image.PreserveAspectFit
        source: "images/plate.png"
        smooth: true
        Behavior on scale {
            PropertyAnimation { easing.type: Easing.OutCubic; duration: 100; }
        }
        MouseArea {
            anchors.fill: parent
            scale: 1.4
            onClicked: Qt.quit()
            onPressed: parent.scale = 0.9
            onReleased: parent.scale = 1.0
        }
    }
}
