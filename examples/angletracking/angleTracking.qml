import QtQuick 2.4
import Box2D 2.0
import "../shared"

Item {
    id: trackJointAngleScreen
    width: 800
    height: 600
    focus: true

    property bool enableTracking: false
    property real requestedAngle: 0

    property vector2d globalPositionRevolute: Qt.vector2d(0,0)
    property vector2d vectorToMouse: Qt.vector2d(0,0)

    function calcDifferenceVector(vector1, vector2) {
        // calculate difference vector
        return (vector1.minus(vector2))
    }

    function calcAngle(differenceVector) {
        var radTodeg = 57.295779513082320876
        return ((Math.atan2(differenceVector.y, differenceVector.x)) * radTodeg)
    }


    Keys.onPressed: {
	    if (event.key === Qt.Key_Up) {
	    	console.log("Key up")
	    	revolute.enableMotor = true
		    revolute.maxMotorTorque = 200
		    enableTracking = true
	    }
		else if (event.key === Qt.Key_Down) {
			console.log("Key down")
		    revolute.enableMotor = false
		    enableTracking = false
		}
        event.accepted = true;
    }

    Text {
        id: helpText
        anchors {
            right: parent.right
            top: parent.top
            left: parent.left
        }
        height: 40
        horizontalAlignment: Text.AlignHCenter;
        text: "Up/Down keys to activate/deactivate motor, Mouse click to set new tracking point (if motor active)"
    }

    Text {
        id: angleText
        anchors {
            right: parent.right
            top: helpText.bottom
            left: parent.left
        }
        horizontalAlignment: Text.AlignHCenter

        text: "Angle: " + requestedAngle.toFixed(0)
        font.pixelSize: 16
        font.bold: true
    }

    // BOX2D WORLD
    World { 
    	id: physicsWorld

    	onStepped: {
    		if(enableTracking) {
	    		var targetAngle = trackJointAngleScreen.requestedAngle
	    		var angleError = revolute.getJointAngle() - targetAngle
	    		var gain = 1.4;
	    		var newMotorSpeed = -gain * angleError

	    		revolute.motorSpeed = newMotorSpeed
	    	}
    	}
	}

    PhysicsItem {
        id: rod
        sleepingAllowed: false
        bodyType: Body.Dynamic
        x: 350
        y: 300

        width: 250
        height: 40

        fixtures: Box {
            width: rod.width
            height: rod.height
            density: 1;
            friction: 1;
            restitution: 0.3;
        }

        Rectangle {
            color: "green"
            radius: 6
            anchors.fill: parent
        }
    }

    PhysicsItem {
        id: middle

        x: 400
        y: 300

        fixtures: Circle { radius: itemShape.radius }

        Rectangle {
            id: itemShape
            radius: width / 2
            width: 40; height: 40
            color: "black"
        }
    }

    RevoluteJoint {
        id: revolute
        maxMotorTorque: 1000
        motorSpeed: 0
        enableMotor: false
        bodyA: middle.body
        bodyB: rod.body
        localAnchorA: Qt.point(20,20)
    }


    Line {
        x: globalPositionRevolute.x
        y: globalPositionRevolute.y
        visible: mouseArea.pressed
        color: "blue"
        rotation: trackJointAngleScreen.requestedAngle

        width: vectorToMouse.length()
        height: 1
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            vectorToMouse = calcDifferenceVector(Qt.vector2d(mouseX, mouseY), globalPositionRevolute)
            trackJointAngleScreen.requestedAngle = calcAngle(vectorToMouse)
        }
        onPressed: {
            vectorToMouse = calcDifferenceVector(Qt.vector2d(mouseX, mouseY), globalPositionRevolute)
            trackJointAngleScreen.requestedAngle = calcAngle(vectorToMouse)
        }
    }

    Component.onCompleted: {
            var bodyAPosition = Qt.vector2d(middle.x, middle.y)
            var localAnchorRevolute = Qt.vector2d(revolute.localAnchorA.x, revolute.localAnchorA.y);

            // position of middle of revolute joint
            globalPositionRevolute = bodyAPosition.plus(localAnchorRevolute)
    }
}
