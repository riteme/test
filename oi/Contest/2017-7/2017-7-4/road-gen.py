#!/usr/bin/env pypy

from sys import *
from random import *

n, m, q, CMAX = map(int, argv[1:])

assert m >= n - 1

s = randint(1, n)
print n, m, s, 0

P = range(1, n + 1)
shuffle(P)

for i in xrange(n):
    if P[i] == 1:
        P[i], P[s - 1] = P[s - 1], P[i]
        break

print " ".join(map(str, P))

for v in xrange(2, n + 1):
    u = randint(1, v - 1)
    print u, v, randint(1, CMAX)

for i in xrange(m - n + 1):
    print randint(1, n), randint(1, n), randint(1, CMAX)

print q
for i in xrange(q):
    print s, randint(1, n)
