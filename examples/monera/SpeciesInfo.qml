import QtQuick 2.0
import Box2D 2.0
import "../shared"

PhysicsItem {
    id: speciesInfo

    property string speciesName: ""
    property alias descriptionText: descriptionText.text
    property alias photoUrl: image.source
    property bool expanded: false
    property real radius: 50

    signal selected()

	width: 100
	height: 100

    world: physicsWorld
    linearDamping: 0.3
    angularDamping: 0.2
	bodyType: Body.Dynamic

    fixtures: Circle {
        radius: speciesInfo.radius
        density: 0.2
        friction: 0.3
        restitution: 0.2
    }

    function toBinomialFormat(speciesName) {
        var subnames = speciesName.split(' ');
        if (subnames.length >= 2)
            return subnames[0] + ' <b>' + subnames[1] + '</b>';
        else
            return ""
    }

    Image {
        id: image
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        height: parent.radius * 2
        width: parent.radius * 2

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            rotation: -speciesInfo.rotation

            onEntered: {
                var dx = mouseX - image.width / 2;
                var dy = mouseY - image.height / 2;
                var abs = Math.sqrt(dx * dx + dy * dy)
                var point = Qt.point(speciesInfo.x, speciesInfo.y);
                var force = Qt.point(-3 * dx / abs, -3 * dy / abs);
                speciesInfo.body.applyLinearImpulse(force, point);
                speciesInfo.angularVelocity = 0;
                speciesInfo.selected();
            }
        }
    }

    Item {
        id: fixed
        anchors.centerIn: parent
        rotation: -parent.rotation
        width: 0
        height: 0
        Item {
            id: info
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: speciesInfo.radius + 10
            }
            height: speciesInfo.radius * 3
            width: height * 3
            transformOrigin: Item.Left

            Behavior on opacity { NumberAnimation { duration: 200 } }
            Behavior on scale { NumberAnimation { duration: 200 } }

            Rectangle {
                anchors.fill: parent
                color: "gray"
                opacity: 0.2
                radius: 10
            }

            Text {
                id: speciesText
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    topMargin: 5
                    leftMargin: 20
                }
                color: "white"
                font.pixelSize: 32
                font.family: "Nokia Sans"
                font.italic: true

                text: toBinomialFormat(speciesName);
            }

            Text {
                id: descriptionText
                anchors {
                    top: speciesText.bottom
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                    topMargin: 10
                    leftMargin: 25
                    rightMargin: 25
                }
                font.pixelSize: 20
                font.family: "Nokia Sans"
                color: "white"
                wrapMode: Text.WordWrap
            }
        }
    }

    states: [
        State {
            name: "expanded"
            when: expanded
            PropertyChanges {
                target: info
                opacity: 1.0
                scale: 1.0
            }
        },
        State {
            name: "retracted"
            when: !expanded
            PropertyChanges {
                target: info
                opacity: 0.0
                scale: 0.3
            }
        }
    ]
}
