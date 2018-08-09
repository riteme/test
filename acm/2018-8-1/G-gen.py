#!/usr/bin/env pypy

from sys import *
from random import *

n, CMAX = map(int, argv[1:])

r = randint(1, n - 1)
print n, r, randint(1, (n - r) * (n - r + 1) / 2)
L = []
for i in xrange(n):
    L.append(randint(1, CMAX - 2))
print " ".join(map(str, L))
for i in xrange(n):
    L[i] = randint(L[i] + 1, CMAX - 1)
print " ".join(map(str, L))
for i in xrange(n):
    L[i] = randint(L[i] + 1, CMAX)
print " ".join(map(str, L))
