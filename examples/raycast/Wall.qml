import QtQuick 2.2
import Box2D 1.1

Body {
    bodyType: Body.Static
    signal beginContact (variant other)
    fixtures: Box {
        anchors.fill: parent
        friction: 1
        density: 1
        onBeginContact: {
            parent.beginContact(other)
        }
    }
    Image {
        source: "images/wall.jpg"
        fillMode: Image.Tile
        anchors.fill: parent
    }
}
