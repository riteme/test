#!/usr/bin/env pypy

from sys import argv
from random import *

n, c, T = map(int, argv[1:])

while T:
    P = range(1, n + 1)

    if c == 1:
        for i in xrange(n):
            p = randrange(0, n)
            P[i], P[p] = P[p], P[i]
    elif c == 2:
        for i in xrange(n):
            p = randint(0, i)
            P[i], P[p] = P[p], P[i]
    else:
        for i in xrange(n):
            x, y = randrange(0, n), randrange(0, n)
            P[x], P[y] = P[y], P[x]

    print " ".join(map(str, P))

    T -= 1
