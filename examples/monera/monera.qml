import QtQuick 2.0
import Box2D 1.1

Rectangle {
    id: root

    property int selected: -1

    color: "black"

    width: 800
    height: 400

    SpeciesModel {
        id: speciesModel
    }


    World {
        id: world
        anchors.fill: parent

        gravity: Qt.point(0, 0)

        Repeater {
            anchors.fill: parent
            model: speciesModel
            delegate: Component {
                SpeciesInfo {
                    id: speciesInfo
                    x: Math.random() * (root.width - radius)
                    y: Math.random() * (root.height - radius)
                    expanded: index == root.selected
                    speciesName: species
                    descriptionText: description
                    photoUrl: photo
                    onSelected: {
                        root.selected = index
                    }
                }
            }
        }

        Wall {
            id: ground
            height: 20
            anchors { left: parent.left; right: parent.right; top: parent.bottom }
        }
        Wall {
            id: ceiling
            height: 20
            anchors { left: parent.left; right: parent.right; bottom: parent.top }
        }
        Wall {
            id: leftWall
            width: 20
            anchors { right: parent.left; bottom: ground.top; top: ceiling.bottom }
        }
        Wall {
            id: rightWall
            width: 20
            anchors { left: parent.right; bottom: ground.top; top: ceiling.bottom }
        }

         DebugDraw {
             anchors.fill: parent
             world: parent
			 visible: false
         }

    }

}
