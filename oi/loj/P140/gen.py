#!/usr/bin/pypy

from sys import *
from random import *

n, m, CMAX = map(int, argv[1:])
assert n <= m
print n, m, randint(1, n)
L = range(1, n + 1)
shuffle(L)
#for i in xrange(n):
#    print L[i], L[(i + 1) % n], randint(1, CMAX)
#for i in xrange(m - n):
for i in xrange(m):
    u = randint(1, n - 1)
    v = randint(u + 1, n)
    if randint(0, 1):
        u, v = v, u
    print u, v, randint(1, CMAX)
