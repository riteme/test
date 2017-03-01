from math import *
from random import *

def force(M, m):
    L = (M[0] - m[0])**2 + (M[1] - m[1])**2
    if L == 0:
        return 0
    return sqrt(M[2] * m[2] / (L + sqrt(L)))

P = []

def generate(n):
    global P

    for i in range(0, n):
        P.append((randint(0, 10), randint(1, 10), randint(1, 100)))

def evaluate(u):
    global P

    vx, vy = 0, 0
    for x, y, m in P:
        dx = u[0] - x
        dy = u[1] - y
        d = sqrt(dx**2 + dy**2)
        f = force((x, y, m), u)
        if f == 0:
            continue
        dx = dx / d * f
        dy = dy / d * f
        vx += dx
        vy += dy

    return (vx, vy)

