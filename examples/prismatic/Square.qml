import QtQuick 2.0
import Box2D 2.0
import "../shared"

Rectangle {
    id: item

    color: "green"
    radius: 6

    property Body body: BoxBody {
        target: item
        world: physicsWorld

        width: item.width
        height: item.height

        sleepingAllowed: false
        bodyType: Body.Dynamic

        density: 10
        friction: 1
        restitution: 0.3
    }
}
