import time
import random

from math import *
from sfml import *

def normalize(vector):
    return vector / sqrt(vector.x **2 + vector.y ** 2)

def get_distance(circle, rect):
    rect_left = rect.position.x
    rect_right = rect.position.x + rect.size.x
    rect_top = rect.position.y
    
    circle_x = circle.position.x + circle.radius
    circle_y = circle.position.y + circle.radius

    if rect_left <= circle_x and circle_x <= rect_right:
        return rect_top - circle_y - circle.radius

    elif circle_x < rect_left:
        return sqrt(
            (circle_x - rect_left) ** 2 + (circle_y - rect_top) ** 2
        ) - circle.radius

    elif circle_x > rect_right:
        return sqrt(
            (circle_x - rect_right) ** 2 + (circle_y - rect_top) ** 2
        ) - circle.radius

class Game(object):
    """A game instance."""
    def __init__(self):
        super(Game, self).__init__()
        self.window = RenderWindow(
            VideoMode(800, 600),
            "Ball",
            window.Style.TITLEBAR | window.Style.CLOSE
        )
        self.window.framerate_limit = 60

        self.setup_wall()
        self.setup_ball()

        self.frame_count = 0
        self.last_time = time.time()

    def setup_wall(self):
       self.wall = RectangleShape()
       self.wall.position = (window.Mouse.get_position(self.window).x - 50, 580)
       self.wall.size = (100, 20)
       self.wall.fill_color = Color(255, 255, 255) 

    def setup_ball(self):
        DIRECTIONS = [-1.0, 1.0]
        self.ball = CircleShape()
        self.ball.position = (random.randrange(25, 775), random.randrange(25, 300))
        self.ball.radius = 25
        self.ball.fill_color = Color(255, 0, 0)

        velocity = Vector2()
        while abs(velocity.x - velocity.y) < 100:
            velocity = Vector2(
                random.randrange(1, 100) * DIRECTIONS[random.randrange(0, len(DIRECTIONS))],
                random.randrange(1, 100) * DIRECTIONS[random.randrange(0, len(DIRECTIONS))]
            )

        velocity = normalize(velocity)
        self.ball_velocity = velocity
        self.ball_speed = 5.0

    def do_events(self):
        for event in self.window.events:
            if type(event) is CloseEvent:
                self.window.close()

            if type(event) is MouseMoveEvent:
                self.wall.position = (event.position.x - 50, self.wall.position.y)

            if type(event) is KeyEvent:
                if event.code == window.Keyboard.ESCAPE:
                    self.window.close()

    def is_lost_ball(self):
        return self.ball.position.y > self.window.size.y + 100

    def do_reflect(self):
        pos = self.ball.position
        left = pos.x
        right = pos.x + self.ball.radius * 2
        top = pos.y
        bottom = pos.y + self.ball.radius * 2
        center_x = pos.x + self.ball.radius

        if top <= 0:
            self.ball_velocity.y *= -1.0

        if left <= 0  or right >=self.window.size.x:
            self.ball_velocity.x *= -1.0

        dist = get_distance(self.ball, self.wall)
        if (-self.ball_speed <= dist and dist <= 0 and
             self.ball_velocity.y > 0):
            self.ball_velocity.y *= -1.0
            self.speed_up()

    def speed_up(self):
        self.ball_speed += 0.1

    def update(self):
        self.ball.position += self.ball_velocity * self.ball_speed

        if self.is_lost_ball():
            self.setup_ball()
        
        self.do_reflect()

    def render(self):
        self.window.clear()
        self.window.draw(self.ball)
        self.window.draw(self.wall)
        self.window.display()

    def run(self):
        while self.window.is_open:
            self.do_events()
            self.update()
            self.render()

            self.frame_count += 1
            current_time = time.time()
            passed = current_time - self.last_time

            if passed > 5.0:
                fps = self.frame_count
                self.last_time = current_time
                self.frame_count = 0

                print("(info) FPS: %s" % fps)
                

    def capture(self):
        return self.window.capture()
