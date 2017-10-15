#!/usr/bin/env pypy

from sys import *
from random import *

n, m = map(int, argv[1:])
P = sorted([randint(0, m) for i in xrange(n - 1)] + [m])
for i in xrange(n - 1, 0, -1):
    P[i] -= P[i - 1]
shuffle(P)

print n
print " ".join(map(str, P))
