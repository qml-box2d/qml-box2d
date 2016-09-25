import QtQuick 2.0
import QtQuick.Window 2.0
import Box2D 2.0
import Box2D.Components 1.0
Window{
    visible: true
    title: qsTr("Monera Example")
    width: 800
    height: 400
    Rectangle {
        id: screen

        property int selected: -1

        color: "black"
        anchors.fill: parent


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
                photoUrl: "qrc:/"+photo
                onSelected: screen.selected = index
            }
        }

        ScreenBoundaries {}

        DebugDraw {
            world: physicsWorld
            visible: false
        }
    }
}
