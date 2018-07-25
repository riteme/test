import time
import sfml.graphics
import sfml.window

def correct(v):
    if v < 0:
        return 0
    elif v > 255:
        return 255
    else:
        return v

def show(func, width = 500, height = 500):
    """
    func(x, y) -> (r, g, b, a)
    """

    window = sfml.graphics.RenderWindow(
        sfml.window.VideoMode(width, height),
        "Viewer"
    )
    window.vertical_synchronization = True

    try:
        pixels = sfml.graphics.VertexArray(
            sfml.graphics.PrimitiveType.POINTS,
            width * height
        )
        for i in range(0, width):
            for j in range(0, height):
                pos = i * width + j
                pixels[pos].position = (i, j)
                
                c = func(i, j)
                if not c is None:
                    pixels[pos].color = sfml.graphics.Color(
                        correct(c[0] * 255.0),
                        correct(c[1] * 255.0),
                        correct(c[2] * 255.0),
                        correct(c[3] * 255.0) 
                    )

        while window.is_open:
            window.clear(sfml.graphics.Color.WHITE)
            window.draw(pixels)
            window.display()

            for event in window.events:
                if type(event) is sfml.window.CloseEvent:
                    window.close()

    except Exception as e:
        print(str(e))
        window.close()
