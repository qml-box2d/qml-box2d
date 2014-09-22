import QtQuick 2.0
import Box2D 2.0
import "../shared"

ImageBoxBody {
    id: woodenBox
    source: "woodenbox.png"

    bodyType: Body.Dynamic
    world: physicsWorld

    density: 1
    friction: 0.3
    restitution: 0.5
}
