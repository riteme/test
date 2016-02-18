#
# Copyright 2000-2025 riteme
#

from math import *
from sfml import *

class Game(object):
	WINDOW_WIDTH = 570
	WINDOW_HEIGHT = 570
	WINDOW_TITLE = "Chess"
	CHESS_RADIUS = 15
	POINT_RADIUS = 3

	CHESS_NONE = 0
	CHESS_WHITE = 1
	CHESS_BLACK = 2

	def __init__(self):
		super(Game, self).__init__()

		self.window = graphics.RenderWindow(
			VideoMode(self.WINDOW_WIDTH, self.WINDOW_HEIGHT),
			self.WINDOW_TITLE
		)
		self.window.framerate_limit = 60

		self.setup_board()
		self.setup_chess()

	# Utility

	def setup_board(self):
		self.board = VertexArray(PrimitiveType.LINES)
		for i in range(0, 19):
			self.board.append(
				Vertex(Vector2(
						self.CHESS_RADIUS + i * 2 * self.CHESS_RADIUS, 
						self.CHESS_RADIUS
					), Color.BLACK
				)
			)

			self.board.append(
				Vertex(Vector2(
						self.CHESS_RADIUS + i * 2 * self.CHESS_RADIUS,
						self.CHESS_RADIUS + 36 * self.CHESS_RADIUS
					), Color.BLACK
				)
			)

			self.board.append(
				Vertex(Vector2(
						self.CHESS_RADIUS,
						self.CHESS_RADIUS + i * 2 * self.CHESS_RADIUS
					), Color.BLACK
				)
			)

			self.board.append(
				Vertex(Vector2(
						self.CHESS_RADIUS + 36 * self.CHESS_RADIUS,
						self.CHESS_RADIUS + i * 2 * self.CHESS_RADIUS
					), Color.BLACK
				)
			)

		self.circles = []

		POSITIONS = [
			(3, 3), (3, 9), (3, 15),
			(9, 3), (9, 9), (9, 15),
			(15, 3), (15, 9), (15, 15)
		]

		for point in POSITIONS:
			x, y = point

			circle = CircleShape()
			circle.radius = self.POINT_RADIUS
			circle.fill_color = Color.BLACK
			circle.position = (
				self.CHESS_RADIUS * 2 * x + self.CHESS_RADIUS - self.POINT_RADIUS,
				self.CHESS_RADIUS * 2 * y + self.CHESS_RADIUS - self.POINT_RADIUS
			)

			self.circles.append(circle)

	def setup_chess(self):
		self.chess = []
		for i in range(0, 19):
			self.chess.append([])

			for j in range(0, 19):
				chess = CircleShape(point_count=128)
				chess.radius = self.CHESS_RADIUS
				chess.fill_color = Color.TRANSPARENT
				chess.position = self.to_position(i, j)
				chess.position -= (self.CHESS_RADIUS, self.CHESS_RADIUS)
				self.chess[-1].append(chess)

		self.current_block = RectangleShape()
		self.current_block.size = (2 * self.CHESS_RADIUS, 2 * self.CHESS_RADIUS)
		self.current_block.position = (-100, -100)
		self.current_block.fill_color = Color(200, 200, 200)

		self.current_color = Color.BLACK

		self.disabled = False
		self.history = []

	def change_color(self):
		if self.current_color == Color.WHITE:
			self.current_color = Color.BLACK
		else:
			self.current_color = Color.WHITE

	def to_position(self, i, j):
		return (
			self.CHESS_RADIUS * 2 * i + self.CHESS_RADIUS,
			self.CHESS_RADIUS * 2 * j + self.CHESS_RADIUS
		)

	def to_index(self, x, y):
		return (
			int(x / (self.CHESS_RADIUS * 2)),
			int(y / (self.CHESS_RADIUS * 2))
		)

	def check_winner(self):
		dx = [0,   1, 1, 1, 0, -1, -1, -1]
		dy = [-1, -1, 0, 1, 1,  1,  0, -1]

		for i in range(0, 19):
			for j in range(0, 19):
				for k in range(0, len(dx)):
					target = self.chess[i][j].fill_color

					if target == Color.TRANSPARENT:
						break

					cx = i + dx[k]
					cy = j + dy[k]
					count = 0

					while count < 4 and 0 <= cx and cx <= 18 and 0 <= cy and cy <= 18:
						if self.chess[cx][cy].fill_color == target:
							count += 1;
							cx += dx[k]
							cy += dy[k]
						else:
							break

					if count == 4:
						return (i, j, cx - dx[k], cy - dy[k], target)

		return None

	def finish(self, result):
		self.disabled = True

		x1, y1, x2, y2, color = result

		x1, y1 = self.to_position(x1, y1)
		x2, y2 = self.to_position(x2, y2)

		self.line = VertexArray(PrimitiveType.LINES, 2)
		self.line[0] = Vertex(
			Vector2(x1, y1), Color.RED
		)
		self.line[1] = Vertex(
			Vector2(x2, y2), Color.RED
		)

		self.info = Text()
		self.info.position = (0, 0)
		self.info.character_size = 30
		self.info.font = Font.from_file("arial.ttf")
		if color == Color.WHITE:
			self.info.string = "White win!"
			self.info.color = Color.WHITE
		else:
			self.info.string = "Black win!"
			self.info.color = Color.BLACK

	# Events

	def do_events(self):
		for event in self.window.events:
			if type(event) is CloseEvent:
				self.window.close()

			elif type(event) is MouseButtonEvent:
				if self.disabled or event.pressed:
					continue

				elif event.button == Mouse.LEFT:
					mx, my = event.position
					i, j = self.to_index(mx, my)

					if self.chess[i][j].fill_color == Color.TRANSPARENT:
						self.chess[i][j].fill_color = self.current_color
						self.history.append((i, j))

						result = self.check_winner()

						if not result is None:
							self.finish(result)

						else:
							self.change_color()

			elif type(event) is MouseMoveEvent:
				mx, my = event.position
				i, j = self.to_index(mx, my)

				self.current_block.position = self.to_position(i, j)
				self.current_block.position -= (self.CHESS_RADIUS, self.CHESS_RADIUS)

			elif type(event) is KeyEvent:
				if not event.released:
					continue

				if event.code == window.Keyboard.ESCAPE:
					self.setup_chess()

				elif event.code == window.Keyboard.Z and event.control:
					if len(self.history) > 0:
						i, j = self.history.pop()
						self.chess[i][j].fill_color = Color.TRANSPARENT

	# Updating

	def update(self):
		pass

	# Rendering

	def draw_board(self):
		self.window.draw(self.board)

		for circle in self.circles:
			self.window.draw(circle)

	def draw_chess(self):
		for line in self.chess:
			for chess in line:
				self.window.draw(chess)

	def render(self):
		self.window.clear(Color(205, 154, 61))
		self.window.draw(self.current_block)
		self.draw_board()
		self.draw_chess()

		if self.disabled:
			self.window.draw(self.line)
			self.window.draw(self.info)

		self.window.display()

	def run(self):
		while self.window.is_open:
			self.do_events()
			self.update()
			self.render()

if __name__ == "__main__":
	game = Game()
	game.run()
