#!/usr/bin/env pypy

from sys import *
from random import *

n, q, d, extra = map(int, argv[1:])

print n, n - 1 + extra, q
P = range(1, n + 1)
shuffle(P)
E = set()
for i in xrange(1, n):
    E.add((P[randrange(max(0, i - d), i)], P[i]))

while len(E) < n:
    u = randint(1, n - 1)
    v = randint(u + 1, n)
    E.add((u, v))

for u, v in E:
    print u, v

for i in xrange(q):
    print randint(1, n), randint(1, n), randint(1, n)
