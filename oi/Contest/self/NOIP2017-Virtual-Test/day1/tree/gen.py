#!/usr/bin/env pypy

from sys import *
from random import *

n, q, d = map(int, argv[1:])

print n, q

P = range(1, n + 1)
E = []
shuffle(P)
for i in xrange(1, n):
    j = randint(max(0, i - d), i - 1)
    E.append((P[i], P[j]))
    print P[i], P[j], randint(0, 10)

for i in xrange(q):
    u, v = choice(E)
    print u, v, randint(0, 10)
