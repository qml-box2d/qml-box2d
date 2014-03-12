import QtQuick 2.0
import Box2D 1.1

Body {
    sleepingAllowed: false
    bullet: true
    fixedRotation: true
	bodyType: Body.Dynamic
    function moveForward() {
        linearVelocity.x = 300;
    }

    function moveBackward() {
        linearVelocity.x = -300;
    }

    function stopMoving() {
        linearVelocity.x = 0;
    }

    function jump() {
        if (linearVelocity.y <= 0 &&
            linearVelocity.y > -50) {
            var impulse = Qt.point(0, -600);
            applyLinearImpulse(impulse, getWorldCenter());
        }
    }

    fixtures: Box {
        anchors.fill: parent
        density: 1;
        friction: 0.3;
        restitution: 0.2;
        groupIndex: 1
    }

    Rectangle {
        anchors.fill: parent
        color: "red"
    }
}
