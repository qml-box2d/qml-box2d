import QtQuick 2.1;
import QtQuick.Window 2.1;
import Box2D 2.0;
//import "shared"

Window {
    id: window;
    width: 1000;
    height: 600;
    visible: true;

    property bool listVisible: true;

    ListModel {
        id: scenesList;
        ListElement {
            name: "accelerometer"
            path: "accelerometer/accelerometer.qml"
        }
        ListElement {
            name: "boxes"
            path: "boxes/boxes.qml"
        }
        ListElement {
            name: "cannon"
            path: "cannon/main.qml"
        }
        ListElement {
            name: "contacts"
            path: "contacts/main.qml"
        }
        ListElement {
            name: "demolition"
            path: "demolition/demolition.qml"
        }
        ListElement {
            name: "distance"
            path: "distance/distance.qml"
        }
        ListElement {
            name: "filtering"
            path: "filtering/filtering.qml"
        }
        ListElement {
            name: "fixtures"
            path: "fixtures/main.qml"
        }
        ListElement {
            name: "friction"
            path: "friction/main.qml"
        }
        ListElement {
            name: "gear"
            path: "gear/main.qml"
        }
        ListElement {
            name: "impulse"
            path: "impulse/impulse.qml"
        }
        ListElement {
            name: "monera"
            path: "monera/monera.qml"
        }
        ListElement {
            name: "motorjoint"
            path: "motorjoint/boat.qml"
        }
        ListElement {
            name: "mouse"
            path: "mouse/main.qml"
        }
        ListElement {
            name: "movingBox"
            path: "movingBox/movingBox.qml"
        }
        ListElement {
            name: "polygons"
            path: "polygons/polygons.qml"
        }
        ListElement {
            name: "prismatic"
            path: "prismatic/prismatic.qml"
        }
        ListElement {
            name: "pulley"
            path: "pulley/main.qml"
        }
        ListElement {
            name: "raycast"
            path: "raycast/main.qml"
        }
        ListElement {
            name: "revolute"
            path: "revolute/revolute.qml"
        }
        ListElement {
            name: "rope"
            path: "rope/main.qml"
        }
        ListElement {
            name: "weld"
            path: "weld/main.qml"
        }
        ListElement {
            name: "wheel"
            path: "wheel/main.qml"
        }
    }

    Loader {
        id: loader;
        anchors {
            left: parent.left;
            right: parent.right;
            top: parent.top;
            bottom: parent.bottom;
            topMargin: backButton.height;
        }
    }

    Rectangle {
        id: backButton;
        anchors.top: parent.top;
        anchors.left: parent.left;
        width: 300;
        height: 40;
        color: "grey";
        border.width: 1;
        border.color: "black";
        visible: !listVisible;

        Text {
            anchors.centerIn: parent;
            text: "Back";
        }

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                listVisible = true;
            }
        }
    }

    ListView {
        id: listView
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.leftMargin: listVisible ? 0 : -width;
        width: 200;
        model: scenesList;
        delegate: Rectangle {
            height: 50;
            width: 200;
            color: "lightgrey"

            Text {
                anchors.centerIn: parent;
                text: name;
            }

            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    loader.source = path
                    listVisible = false;
                }
            }
        }


    }
}

