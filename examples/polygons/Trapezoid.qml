import QtQuick 2.0
import Box2D 2.0
import "../shared"

PhysicsItem {
    world: physicsWorld
    sleepingAllowed: false
	bodyType: Body.Dynamic

    fixtures: Polygon {
        density: 1
        friction: 0.3
        restitution: 0.5
        vertices: [
            Qt.point(-10.5, 0),
            Qt.point(0, 100),
            Qt.point(110, 100),
            Qt.point(100, 0)
        ]
    }
}
