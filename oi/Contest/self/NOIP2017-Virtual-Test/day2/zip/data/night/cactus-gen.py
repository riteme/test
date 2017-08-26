#!/usr/bin/env pypy

from random import *
from sys import *

n, q, d = map(int, argv[1:])

E = []
P = range(1, n + 1)
shuffle(P)
father = [0] * (n + 1)
cover = [0] * (n + 1)
for i in xrange(1, n):
    u = P[randrange(max(0, i - d), i)]
    v = P[i]
    father[v] = u
    p = v

    if randint(0, 1) & 1:
        while father[p] and not cover[p] and randint(0, 5) >= 1:
            p = father[p]

    E.append((u, v))
    if p != u and p != v:
        E.append((v, p))

        while v != p:
            cover[v] = 1
            v = father[v]

print n, len(E), q
for u, v in E:
    print u, v

for i in xrange(q):
    print randint(1, n), randint(1, n), randint(1, n)
