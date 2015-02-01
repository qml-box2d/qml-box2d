import QtQuick 2.0
import Box2D 2.0
import "../shared"

Item {
    id: screen

    width: 800
    height: 600

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
