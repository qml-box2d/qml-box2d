import QtQuick 2.0
import Box2D 2.0
import "../shared"

Item {
    id: woodenBox

    width: 100
    height: 100

    BoxBody {
        id: body

        world: physicsWorld
        target: woodenBox
        bodyType: Body.Dynamic

        density: 1
        friction: 0.4
        restitution: 0.5

        width: woodenBox.width
        height: woodenBox.height
    }

    Image {
        anchors.fill: parent
        anchors.margins: -1
        source: "images/woodenbox.png"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: body.applyTorque(400)
    }
}
