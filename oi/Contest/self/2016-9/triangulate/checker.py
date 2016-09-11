#!/usr/bin/env python3

import sys

from sfml import *

if len(sys.argv) < 3:
    print("Usage: %s [STANDARD] [USER]" % sys.argv[0])
    exit(0)

width = 0
height = 0
standard = []
user = []

def read_points(reader):
    L = []
    for line in reader:
        x1, y1, x2, y2, x3, y3 = [
            float(x) for x in line.split(" ")
        ]

        L.append((x1, y1))
        L.append((x2, y2))
        L.append((x3, y3))

    return L

print("(info) Reading data...")

with open(sys.argv[1]) as reader:
    width, height = [int(x) for x in reader.readline().split(" ")]
    standard = read_points(reader)

with open(sys.argv[2]) as reader:
    user = read_points(reader)

if len(standard) % 3 != 0:
    print("(error) Standard input format error.")
    exit(1)
if len(user) % 3 != 0:
    print("(error) User input format error.")
    exit(1)

print("(info) Rendering...")

def render(triangles, target, color):
    target.clear(Color.WHITE)

    for i in range(0, len(triangles), 3):
        triangle = ConvexShape()
        triangle.point_count = 3
        triangle.set_point(0, triangles[i])
        triangle.set_point(1, triangles[i + 1])
        triangle.set_point(2, triangles[i + 2])
        triangle.fill_color = color

        target.draw(triangle)

target = RenderTexture(width, height)
render(standard, target, Color(0, 0, 0, 155))
render(user, target, Color(55, 0, 55, 155))

print("(info) Saving to file...")

target.texture.to_image().to_file("output.bmp")
