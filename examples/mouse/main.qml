import QtQuick 2.2
import Box2D 1.1


Rectangle {
    width: 800
    height: 600
    id: global
    property bool dragged: false
    property variant joint: null
    property variant body: null

    Component {
        id: jointComponent
        MouseJoint {
            world: world
            bodyA: anchor
            dampingRatio: 0.8
            target: Qt.point(350.0,200.0);
            maxForce: 100

        }
    }

    MouseArea {
        id: mouseArea
        onPressed: {
            global.createJoint(mouse.x,mouse.y);
        }
        onReleased: {
            global.destroyJoint();
        }

        onPositionChanged: {
            if(global.dragged == true)
            {
                global.joint.target = Qt.point(mouse.x,mouse.y);
            }
        }
        anchors.fill: parent


    }

    function createJoint(x,y) {
        if(global.joint != null) destroyJoint();
        var body = global.body;
        if(body == null) return;
        var mouseJoint = jointComponent.createObject(world);
        mouseJoint.target = Qt.point(x,y);
        mouseJoint.bodyB = body;
        mouseJoint.maxForce = body.getMass() * 30.0;
        global.dragged = true;
        global.joint = mouseJoint;
    }

    function destroyJoint() {
        if(global.dragged == false) return;
        if(global.joint != null) {
            global.dragged = false;
            global.joint.destroy();
            global.joint = null;
            global.body = null;
        }
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
                x: (40 + Math.random() * 720)
                y: (40 + Math.random() * 520)
                width: (20 + Math.random() * 100)
                height: (20 + Math.random() * 100)
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
                    color: Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
                    border.color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
                    smooth: true
                }
                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true
                    onPressed: {
                        global.body = parent
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
