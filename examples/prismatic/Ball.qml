import QtQuick 2.0
import Box2D 1.1

Body {
    fixedRotation: false
    sleepingAllowed: false
	bodyType: Body.Dynamic
    fixtures: Circle {
	id: circleShape
	radius: width / 2
	anchors.fill: parent
	density: 1;
	friction: 1;
        restitution: 0.3;
    }

    Rectangle {
	id: itemShape
	radius: 180
	width: parent.width
	height: parent.height
	x: circleShape.x - circleShape.radius
	y: circleShape.y - circleShape.radius

        gradient: Gradient {
            GradientStop { position: 0.0; color: "red" }
            GradientStop { position: 0.5; color: "yellow" }
            GradientStop { position: 1.0; color: "green" }
        }

    }
}
