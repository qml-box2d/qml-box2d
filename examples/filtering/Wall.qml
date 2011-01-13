import Qt 4.7
import Box2D 1.0

Body {
    bodyType: Body.Static
    fixtures: Box {
        anchors.fill: parent
        categories: Box.Category1
    }
}
