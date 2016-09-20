import QtQuick 2.0
import Box2D 2.0
import Box2D.Components 1.0


ImageBoxBody {
    id: woodenBox
    source: "qrc:/images/woodenbox.png"

    bodyType: Body.Dynamic
    world: physicsWorld

    density: 1
    friction: 0.3
    restitution: 0.5
}
