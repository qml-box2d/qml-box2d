import Qt 4.7

Repeater {
    id: building
    property int floors: 3
    property int stairways: 3
    height: floors * 20
    width: stairways * 20
    model: floors * stairways
    delegate: WoodenBox {
        x: building.x + index % stairways * 20
        y: building.y + Math.floor(index / stairways) * 20;
        width: 20
        height: 20
    }
}
