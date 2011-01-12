import Qt 4.7
import Box2D 1.0

Body {
    id: polygon

    width: 100;
    height: 100;
    sleepingAllowed: false

    fixtures: Polygon {
        density: 1
        friction: 0.3
        restitution: 0.5
        vertices: [
            Qt.point(-10.5, 0),
            Qt.point(0, 100),
            Qt.point(110, 100),
            Qt.point(100, 0)
        ]
    }
}
