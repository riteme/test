#!/usr/bin/env python3

from sfml import *


def dot(a, b):
    return a.x * b.x + a.y * b.y


def cross(a, b):
    return a.x * b.y - a.y * b.x


def rasterizer(triangle, width, height):
    MASK = Color.WHITE

    result = Image.create(width, height, Color.BLACK)
    points = sorted(triangle, key = lambda vec: vec.x)

    up = points[0]
    mid = points[1]
    down = points[2]
    current = mod
    while cross(up - down, mid - down) * cross(up - down, current - down) > 0:
        result[current.x][current.y] = MASK

        scanner = current + (0, 1)


width = 10
height = 10
triangle = [
    Vector2(2, 2),
    Vector2(7, 10),
    Vector2(5, 7)
]

rasterizer(triangle, width, height)
