import QtQuick 2.0
import Box2D 1.1

Item {
    id: screen
    width: 800
    height: 600
    World {
        id: world;
        anchors.fill: parent

        Repeater {
            model: 5
            delegate: Body {
                x: index * 150 + 10;
                y: Math.random() * (screen.height / 3);
                width: 50;
                height: 50;
                sleepingAllowed: false
				bodyType: Body.Dynamic
                fixtures: Box {
                    anchors.fill: parent
                    density: 1
                    friction: 0.3
                    restitution: 0.5
                    categories: Box.Category2
                    collidesWith: Box.Category1 | Box.Category3 | Box.Category4
                }
                rotation: Math.random() * 90;
                Rectangle {
                    anchors.fill: parent
                    color: "blue"
                    opacity: 0.5
                }
            }
        }

        Repeater {
            model: 5
            delegate: Body {
                x: index * 150 + 10;
                y: Math.random() * (screen.height / 3);
                width: 50;
                height: 50;
                sleepingAllowed: false
				bodyType: Body.Dynamic
                fixtures: Box {
                    anchors.fill: parent
                    density: 1
                    friction: 0.3
                    restitution: 0.5
                    categories: Box.Category3
                    collidesWith: Box.Category1 | Box.Category2 | Box.Category4
                }
                rotation: Math.random() * 90;
                Rectangle {
                    anchors.fill: parent
                    color: "red"
                    opacity: 0.5
                }
            }
        }

        Repeater {
            model: 5
            delegate: Body {
                x: index * 150 + 10;
                y: Math.random() * (screen.height / 3);
                width: 50;
                height: 50;
                sleepingAllowed: false
                fixedRotation: true
				bodyType: Body.Dynamic
                fixtures: Box {
                    anchors.fill: parent
                    density: 1
                    friction: 0.3
                    restitution: 0.5
                    categories: Box.Category4
                    collidesWith: Box.All
                }
                rotation: Math.random() * 90;
                Rectangle {
                    anchors.fill: parent
                    color: "green"
                    opacity: 0.5
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
    }
}
