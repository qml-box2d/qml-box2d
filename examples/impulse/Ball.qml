import QtQuick 2.0
import Box2D 2.0
import "../shared"

PhysicsItem {
    id: ball

    Rectangle {
        id: circle

        color: "green"
        radius: width / 2
        width: 100
        height: 100
        anchors.centerIn: parent
    }

    property Body body: CircleBody {
        target: ball
        world: physicsWorld
        sleepingAllowed: false
        bodyType: Body.Dynamic

        radius: circle.radius
        x: -radius
        y: -radius
        density: 1
        friction: 1
        restitution: 0.5
    }
}
