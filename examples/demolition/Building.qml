import QtQuick 2.0

Repeater {
    id: building

    property int floors: 3
    property int stairways: 3

    property int blockWidth: 20
    property int blockHeight: 20

    width: stairways * blockWidth
    height: floors * blockHeight

    model: floors * stairways

    delegate: WoodenBox {
        x: building.x + index % stairways * width
        y: building.y + Math.floor(index / stairways) * height;

        width: blockWidth
        height: blockHeight
    }
}
