import pyglet

window = pyglet.window.Window(caption="Pyglet Test")
label = pyglet.text.Label(
        "Hello, pyglet!",
        font_name="Ubuntu Mono",
        font_size=36,
        color=(255, 0, 0, 255),
        x=window.width//2,
        y=window.height//2,
        anchor_x="center",
        anchor_y="center"
    )

@window.event
def on_draw():
    global window
    global label

    window.clear()
    label.draw()

pyglet.app.run()
