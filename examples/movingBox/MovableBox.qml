import QtQuick 2.0
import Box2D 2.0
import "../shared"

PhysicsItem {
    id: box

    sleepingAllowed: false
    bullet: true
    fixedRotation: true
    bodyType: Body.Dynamic

    function moveForward() {
        body.linearVelocity.x = 10;
    }

    function moveBackward() {
        body.linearVelocity.x = -10;
    }

    function stopMoving() {
        body.linearVelocity.x = 0;
    }

    function jump() {
        var impulse = Qt.point(0, -10);
        body.applyLinearImpulse(impulse, body.getWorldCenter());
    }

    fixtures: Box {
        width: box.width
        height: box.height

        density: 1
        friction: 0.3
        restitution: 0.2
        groupIndex: 1
    }

    Rectangle {
        anchors.fill: parent
        color: "red"
    }
}
