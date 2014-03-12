import QtQuick 2.0
import Box2D 1.1

Body {
    width: 100;
    height: 100;
    sleepingAllowed: false
	bodyType: Body.Dynamic
    fixtures: Box {
        anchors.fill: parent
        density: 1;
        friction: 0.3;
        restitution: 0.5;
    }

    Image { anchors.fill: parent; source: "woodenbox.png" }
}
