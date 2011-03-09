import Qt 4.7
import Box2D 1.0

Body {
    fixedRotation: false
    sleepingAllowed: false

    fixtures: Box {
        anchors.fill: parent
        density: 1;
        friction: 1;
        restitution: 0.3;
    }

    Rectangle {
        id: itemShape
        color: "green"
        anchors.fill: parent
    }
}
