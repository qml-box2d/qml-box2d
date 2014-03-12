import QtQuick 2.0
import Box2D 1.1

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
        Body {
            id: wheelBody
            sleepingAllowed: true
			bodyType: Body.Dynamic
			width:80
			height:80
            fixtures: Circle {
                id: circle
                radius: 40
                density: 6
                friction: 1.0
                restitution: 0.6
            }
            Image {
                id: circleRect
                anchors.centerIn: parent
                smooth: true
                source: "images/wheel.png"
                MouseArea {
                    anchors.fill: parent
                    onReleased: timer.running = false
                    onPressed: {
                        if(wheelBody.x < (world.width / 2)) {
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
        contentWidth: world.width // * 2
        contentHeight: world.height


        World {
            id: world
            width: screen.width
            height: screen.height

            MouseArea {
                anchors.fill: parent
                onPressAndHold: {
                    var wheel = wheelComponent.createObject(world)
                    wheel.x = mouse.x
                    wheel.y = mouse.y
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
    }


    Image {
        anchors {
            top: parent.top; topMargin: 10
            right: parent.right; rightMargin: 20
        }

        fillMode: Image.PreserveAspectFit
        source: "images/plate.png"
        smooth: true
        MouseArea {
            anchors.fill: parent
            scale: 1.4
            Behavior on scale {
                PropertyAnimation { duration: 100 }
            }
            onClicked: Qt.quit()
            onPressed: parent.scale = 0.9
            onReleased: parent.scale = 1.0
        }
    }
	DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: world
            opacity: 0.75
            visible: false
        }
}
