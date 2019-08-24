#!/usr/bin/env pypy

from sys import *
from random import *

n, CMAX = map(int, argv[1:])

print n, randint(0, CMAX)
P = range(1, n + 1)
shuffle(P)
for i in xrange(1, n):
    u = P[randrange(max(0, i - 30), i)]
    v = P[i]
    print u, v, randint(0, CMAX)
