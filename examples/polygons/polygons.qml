import QtQuick 2.0
import Box2D 2.0
import "../shared"

Item {
    id: screen

    width: 800
    height: 600


    readonly property int wallMeasure: 32
    readonly property int minBallPos: Math.ceil(wallMeasure)
    readonly property int maxBallPos: Math.floor(screen.width - wallMeasure)

    function xPos() {
        return (Math.floor(Math.random() * (maxBallPos - minBallPos)) + minBallPos)
    }

    World { id: physicsWorld; }

    Repeater {
        model: 10
        delegate: Trapezoid {
            x: xPos();
            y: Math.random() * (screen.height / 3);
            rotation: Math.random() * 90;
        }
    }

    ScreenBoundaries {}

    DebugDraw {
        world: physicsWorld
        opacity: 0.75
        visible: true
    }
}
