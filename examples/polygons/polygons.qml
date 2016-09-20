import QtQuick 2.0
import QtQuick.Window 2.0
import Box2D 2.0
import Box2D.Components 1.0

Window{
    visible: true
    title: qsTr("Polygons Example")
    width: 800
    height: 600
    Item {
        id: screen

        anchors.fill: parent

        World { id: physicsWorld; }

        Repeater {
            model: 10
            delegate: Trapezoid {
                x: index * 150 + 10;
                y: Math.random() * (screen.height / 3);
                rotation: Math.random() * 90;
            }
        }

        ScreenBoundaries {}

        DebugDraw {
            world: physicsWorld
            opacity: 0.75
        }
    }
}
