import QtQuick
import Box2D
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
