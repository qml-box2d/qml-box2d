import QtQuick

Rectangle {
    id: frameTubeObject

    property alias rotation: lineRotation.angle
    
    antialiasing: true 

    transform: Rotation {
        id: lineRotation
        origin {
        x: 0
        y: (height / 2)
        }
        axis {x: 0; y: 0; z: 1}
        angle: 0
    }
}
