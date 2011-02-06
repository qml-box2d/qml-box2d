import Qt 4.7
import Box2D 1.0

Body {
    width: 100
    height: 100
    sleepingAllowed: false
    bodyType: Body.Dynamic

    fixtures: Box {
        anchors.fill: parent
        density: 1;
        friction: 0.3;
        restitution: 0.5;
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
    }
}
