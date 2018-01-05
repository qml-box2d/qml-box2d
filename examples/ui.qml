import QtQuick 2.4;
import QtQuick.Window 2.1;
import QtQuick.Layouts 1.1
import Box2D 2.0;
//import "shared"

Window {
    id: window;
    width: 800 + listView.width;
    height: 600

    visible: true;

    ListModel {
        id: scenesList;
        ListElement {
            name: "accelerometer"
            path: "accelerometer/accelerometer.qml"
        }
        ListElement {
            name: "angletracking"
            path: "angletracking/angleTracking.qml"
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
            name: "revolute plot angle"
            path: "revoluteplotangle/revolutePlotAngle.qml"
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

    RowLayout {
        width: parent.width
        height: parent.height
        spacing: 0

        // 1st pane
        Rectangle {
            id: firstPane
            Layout.preferredWidth: 200
            Layout.preferredHeight: parent.height
            Layout.fillHeight: true

            border.color: "#DEDEDE"
            border.width: 1


            MouseArea {
            anchors.fill: listView
            onWheel: listView.flick(0, wheel.angleDelta.y * 5)
            }


            ListView {
                id: listView

                width: parent.width
                height: parent.height

                // focus: true

                model: scenesList;
                delegate: Item {
                    height: 50;
                    width: parent.width;

                    Text {
                        anchors.centerIn: parent;
                        text: name;
                    }

                    MouseArea {
                        anchors.fill: parent;
                        onClicked: {
                            listView.currentIndex = index
                            sceneLoader.source = path
                        }
                    }
                }

                highlightFollowsCurrentItem: true
                highlight: Rectangle {
                    id: highlightRectangle
                    width: parent.width
                    height: 50
                    color: "#DEDEDE"
                }
            }
        }

        // 2nd pane
        Item {
            id: secondPane
            Layout.preferredWidth: 800
            Layout.preferredHeight: parent.height
            Layout.fillHeight: true

            Loader {
                id: sceneLoader
                width: parent.width
                height: parent.height
                focus: true
            }
        }
    }
}

