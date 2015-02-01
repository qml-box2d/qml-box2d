import QtQuick 2.0
import Box2D 2.0
import "../shared"

Rectangle {
    id: screen

    property int selected: -1

    color: "black"

    width: 800
    height: 400

    SpeciesModel {
        id: speciesModel
    }

    World {
        id: physicsWorld
        gravity: Qt.point(0, 0)
    }

    Repeater {
        anchors.fill: parent
        model: speciesModel
        delegate: SpeciesInfo {
            id: speciesInfo
            x: Math.random() * (screen.width - radius)
            y: Math.random() * (screen.height - radius)
            expanded: index == screen.selected
            speciesName: species
            descriptionText: description
            photoUrl: photo
            onSelected: screen.selected = index
        }
    }

    ScreenBoundaries {}

    DebugDraw {
        world: physicsWorld
        visible: false
    }
}
