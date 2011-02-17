import Qt 4.7
import Box2D 1.0

Body {
    fixedRotation: false
    sleepingAllowed: false

    fixtures: Circle {
	id: circleShape
	radius: width / 2
	anchors.fill: parent
	density: 1;
	friction: 1;
	restitution: 0.0;
    }

    Rectangle {
	id: itemShape
	color: "green"
	radius: 180
	width: parent.width
	height: parent.height
	x: circleShape.x - circleShape.radius
	y: circleShape.y - circleShape.radius
    }
}
