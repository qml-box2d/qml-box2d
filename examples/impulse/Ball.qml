import QtQuick 2.0
import Box2D 1.1

Body {
    fixedRotation: false
    sleepingAllowed: false
    bodyType: Body.Dynamic
    fixtures: Circle {
        id: circleShape
        radius: parent.width / 2
        anchors.fill: parent
        density: 1;
        friction: 1;
        restitution: 0.5;
    }
    
    Rectangle {
        id: itemShape
        color: "green"
        radius: parent.width / 2
        width: parent.width
        height: parent.height
    }
}
