import QtQuick 2.0
import Box2D 2.0
import "../shared"

PhysicsItem {
    id: box

    width: 100
    height: 100
    sleepingAllowed: false
	bodyType: Body.Dynamic

    fixtures: Box {
        width: box.width
        height: box.height
        density: 1
        friction: 0.3
        restitution: 0.5
    }

    Image { anchors.fill: parent; source: "woodenbox.png" }
}
