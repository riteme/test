#!/usr/bin/env pypy

from random import choice, randint, shuffle

N = 1000000
Q = 20000

print("0 %s" % N)

for i in range(0, Q):
    x1 = randint(1, N)
    x2 = randint(x1, N)
    y1 = randint(1, N)
    y2 = randint(y1, N)
    t = randint(1, 2)

    if t == 1:  # ADD
        print("1 %s %s %s %s %s" % (x1, y1, x2, y2, randint(1, 10)))
    else:  # QUERY
        print("2 %s %s %s %s" % (x1, y1, x2, y2))

print("3")
