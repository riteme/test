#!/usr/bin/env pypy

from sys import *
from math import *
from random import *

n, w, h, p, R0 = map(int, argv[1:])

print 0, 0, w, h
P = [(0, 0, 0.1), (w, h, 0.1)]
print n
while len(P) < n + 2:
    x0 = randint(0, w)
    y0 = randint(0, h)
    r0 = 1e99
    for x, y, r in P:
        r0 = min(r0, sqrt((x - x0)**2 + (y - y0)**2) - r)
    if r0 >= 1:
        P.append((x0, y0, R0))
        print x0, y0, R0
    #if randint(0, 99) >= p and r0 >= 1e-3:
    #    r0 = randint(0, min(R0, int(r0)))
    #if r0 >= 1e-3:
    #    r0 = int(r0)
    #    P.append((x0, y0, r0))
    #    print x0, y0, r0
