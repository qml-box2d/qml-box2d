import QtQuick
import Box2D
import "../shared"

Item {
    id: revoluteArea
    width: parent.width
    height: parent.height
    focus: true

    property Body pressedBody: null
    readonly property int rodDiameter: 40 
    readonly property int rodOffset: (rodDiameter / 2)
    readonly property int rodLength: (revoluteArea.height / 2) + (rodDiameter * 2 / 3) 
    readonly property int jointPosY: (revoluteArea.height / 2) - (rodDiameter / 2) 

    function getJointAngle() {
        return revolute.getJointAngle()
    }

    function getJointSpeed() {
        return revolute.getJointSpeed()
    }

    Text {
        anchors {
            right: parent.right
            top: parent.top
            left: parent.left
        }
        height: 40
        horizontalAlignment: Text.AlignHCenter;
        text: "Use mouse to manipulate rod."
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


    // BOX2D WORLD
    World { id: physicsWorld }

    Body {
        id: anchor
        world: physicsWorld
    }

    PhysicsItem {
        id: rod

        sleepingAllowed: false
        bodyType: Body.Dynamic
        x: (parent.width / 2) - (rodDiameter)
        y: jointPosY


        width: rodLength
        height: rodDiameter

        fixtures: Box {
            width: rod.width
            height: rod.height
            density: 1;
            friction: 0;
            restitution: 0;
        }

        Rectangle {
            id: rodRectangle
            color: "green"
            radius: 6
            anchors.fill: parent
        }

        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
            onPressed: {
                mouse.accepted = false;
                pressedBody = rod.body
            }
        }
    }

    PhysicsItem {
        id: middle

        x: (parent.width / 2) - (rodDiameter / 2)
        y: jointPosY


        fixtures: Circle { radius: itemShape.radius }

        Rectangle {
            id: itemShape
            radius: width / 2
            width: rodDiameter;
            height: rodDiameter
            color: "black"
        }
    }

    RevoluteJoint {
        id: revolute
        maxMotorTorque: 10
        motorSpeed: 0
        enableMotor: true
        bodyA: middle.body
        bodyB: rod.body
        localAnchorA: Qt.point(20,20)
        enableLimit: true
        lowerAngle: 267
        upperAngle: -87
    }

    // Debug
    DebugDraw {
        id: debugDraw
        world: physicsWorld
        opacity: 0.5
        visible: false
    }

    Rectangle {
        id: debugButton
        x: 30
        y: 30
        width: debugButtonText.width + 20
        height: 30

        Item {
            anchors.centerIn: parent
            anchors.margins: 10
            Text {
                id: debugButtonText
                text: "DebugDraw"
                anchors.centerIn: parent
                anchors.margins: 10
            }
        }

        color: "#DEDEDE"
        border.color: "#999"
        radius: 5
        MouseArea {
            acceptedButtons: Qt.LeftButton
            anchors.fill: parent
            propagateComposedEvents: false
            onPressed: {
                debugDraw.visible = !debugDraw.visible
            }
        }
    }


}
