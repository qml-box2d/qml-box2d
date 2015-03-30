import QtQuick 2.0
import Box2D 2.0

Rectangle {
    id: ball

    radius: 180

    gradient: Gradient {
        GradientStop { position: 0.0; color: "red" }
        GradientStop { position: 0.5; color: "yellow" }
        GradientStop { position: 1.0; color: "green" }
    }

    property Body body: Body {
        target: ball
        world: physicsWorld

        fixedRotation: false
        sleepingAllowed: false
        bodyType: Body.Dynamic

        Circle {
            radius: width / 2
            density: 1
            friction: 1
            restitution: 0.3
        }
    }
}
