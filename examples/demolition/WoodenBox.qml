import QtQuick 2.0
import Box2D 1.1

Image {
    id: box

    width: 100
    height: 100
    transformOrigin: Item.TopLeft

    Body {
        id: body

        world: physicsWorld
        target: box
        bodyType: Body.Dynamic

        fixtures: Box {
            width: box.width
            height: box.height

            density: 1
            friction: 0.4
            restitution: 0.5
        }
    }

    Image {
        anchors.fill: parent
        source: "images/woodenbox.png"
        anchors.margins: -1
    }

    MouseArea {
        anchors.fill: parent
        onClicked: body.applyTorque(400)
    }
}
