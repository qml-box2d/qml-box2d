import Box2D 2.0

/*
  This body places 32-pixel wide invisible static bodies around the screen,
  to avoid stuff getting out.
*/
Body {
    world: physicsWorld

    Box {
        y: screen.height
        width: screen.width
        height: 32
    }
    Box {
        y: -32
        height: 32
        width: screen.width
    }
    Box {
        x: -32
        width: 32
        height: screen.height
    }
    Box {
        x: screen.width
        width: 32
        height: screen.height
    }
}
