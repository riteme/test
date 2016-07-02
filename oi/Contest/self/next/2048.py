from random import *

DIRECTION_UP = 1
DIRECTION_DOWN = 2
DIRECTION_LEFT = 3
DIRECTION_RIGHT = 4

a = [
[0, 0, 0, 0],
[0, 0, 0, 0],
[0, 0, 0, 0],
[0, 0, 0, 0]
]

def is_dead():
    dead = True

    for i in range(0, 4):
        for j in range(0, 4):
            if a[i][j] == 0:
                dead = False
            if (
                (i - 1 >= 0 and a[i - 1][j] == a[i][j]) or
                (i + 1 < 4 and a[i + 1][j] == a[i][j]) or
                (j - 1 >= 0 and a[i][j - 1] )
