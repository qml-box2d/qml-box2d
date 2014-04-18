import QtQuick 2.0
import Box2D 1.1

Body {
    sleepingAllowed: false
    bullet: true
    fixedRotation: true
    bodyType: Body.Dynamic
    function moveForward() {
        linearVelocity.x = 10;
    }

    function moveBackward() {
        linearVelocity.x = -10;
    }

    function stopMoving() {
        linearVelocity.x = 0;
    }

    function jump() {
        var impulse = Qt.point(0, -10);
        applyLinearImpulse(impulse, getWorldCenter());
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
