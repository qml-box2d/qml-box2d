import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Box2D Examples")

    // we use this to block the button if a example is open
    property bool homePage: true
    // Here is all our examples
    property var box2dPages: [
            "accelerometer/accelerometer.qml", "boxes/boxes.qml", "cannon/main.qml", "contacts/main.qml",
            "demolition/demolition.qml", "distance/distance.qml", "filtering/filtering.qml", "fixtures/main.qml",
            "friction/main.qml", "gear/main.qml", "impulse/impulse.qml", "monera/monera.qml",
            "motorjoint/boat.qml", "mouse/main.qml", "movingBox/movingBox.qml", "polygons/polygons.qml",
            "prismatic/prismatic.qml", "pulley/main.qml", "raycast/main.qml", "revolute/revolute.qml",
            "rope/main.qml", "weld/main.qml", "wheel/main.qml",
    ]




    // Our Example Loader with connection points for when things are closed
    Loader{
        id: pages
        anchors.fill: parent
        Connections {
            target: pages.item
            onClosing: {
                homePage = !homePage
            }
        }
    }



    ListView{
        id: view
        height: root.height
        width: root.width
        currentIndex: -1
        spacing: 2
        model: box2dPages
        delegate: Rectangle{
            width: view.width
            height: view.height / 10
            anchors.horizontalCenter: parent.horizontalCenter
            color: ListView.isCurrentItem ? "#e3e3e3" : "white"
            radius: 2
            border{
                width: 1
                color: "#88000000"
            }
            Text {
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: parent.height / 1.4
                text:{
                    var c = modelData
                    var u = c.substring(0,c.indexOf("/"))
                    var t = u.replace(/\.qml/g,'')
                    t
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked:  {
                    if(homePage){
                        view.currentIndex = index
                        // reset the page no matter what
                        pages.source = ""
                        pages.source = "qrc:/" + modelData
                        homePage = !homePage
                    }
                }
            }
        }
    }
}
