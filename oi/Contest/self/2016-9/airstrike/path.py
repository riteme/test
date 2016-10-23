from random import *


def generate_vertical(start, end, count, padding):
    fx, fy = start
    dx, dy = end

    assert fx == dx, "Vertical generation."
    assert count >= 2, "Invalid argument: count."

    sample = set([fy, dy])
    while len(sample) < count:
        sample.add(randint(min(fy, dy), max(fy, dy)))

    L = []
    for y in sample:
        L.append((randint(fx - padding, fx + padding), y))

    def up_to_down(t):
        return -t[1]
    def down_to_up(t):
        return t[1]

    if fy >= dy:
        return sorted(L, key = up_to_down)
    else:
        return sorted(L, key = down_to_up)


def generate_horizontal(start, end, count, padding):
    fx, fy = start
    dx, dy = end

    assert fy == dy, "Horizontal generation."
    assert count >= 2, "Invalid argument: count."

    sample = set([fx, dx])
    while len(sample) < count:
        sample.add(randint(min(fx, dx), max(fx, dx)))

    L = []
    for x in sample:
        L.append((x, randint(fy - padding, fy + padding)))

    def left_to_right(t):
        return t[0]
    def right_to_left(t):
        return -t[0]

    if fx <= dx:
        return sorted(L, key = left_to_right)
    else:
        return sorted(L, key = right_to_left)
