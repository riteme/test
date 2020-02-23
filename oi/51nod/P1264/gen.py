#!/usr/bin/python

from itertools import product

V = range(0, 5)
P = list(product(V, V))
T = list(product(P, P, P, P))

print len(T)
for (x1, y1), (x2, y2), (x3, y3), (x4, y4) in T:
    print x1, y1, x2, y2, x3, y3, x4, y4
