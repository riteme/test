#!/usr/bin/pypy

from sys import *
from random import *

n, m, CMAX, d1, d2 = map(int, argv[1:])
#print randint(0, n)
print 1
x0, y0 = randint(-20, -10), randint(-20, -10)
dx, dy = randint(-d1, -1), randint(1, d1)
x1, y1 = x0 + dx, y0 + dy
dx, dy = -dy, dx
print x0, y0
print x1, y1
print x1 + dx, y1 + dy
print x0 + dx, y0 + dy
print n
for i in xrange(n):
    print m
    x, y = randint(0, CMAX), randint(0, CMAX)
    for j in xrange(m):
        print x, y, 0
        x += randint(-d2, d2)
        y += randint(-d2, d2)
        x = max(0, x)
        y = max(0, y)

