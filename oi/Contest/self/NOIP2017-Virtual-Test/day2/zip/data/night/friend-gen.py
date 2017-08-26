#!/usr/bin/env pypy

from random import *
from sys import *

n, q, K, RA, RB = map(int, argv[1:])
R = RA / RB

E = []
Q = []

Q.append((n, n, n))
Q.append((n, n, randint(1, n - 1)))
n -= 1

nodes = []
w = n // K
for l in xrange(1, n + 1, w):
    r = min(n, l + w - 1)
    m = int((r - l + 1) * R)

    nodes.append(randint(l, r))
    if l == 1:
        for j in xrange(l + 1, r + 1, 2):
            E.append((l, j))

            if j < r:
                E.append((j, j + 1))
                E.append((j + 1, l))
    elif l == w + 1:
        for j in xrange(l, r):
            E.append((j, j + 1))
        E.append((r, l))
    else:
        for j in xrange(m):
            u = randint(l, r)
            v = randint(l, r)
            E.append((u, v))

for i in xrange(1, len(nodes)):
    j = randrange(0, i)
    E.append((nodes[i], nodes[j]))

for i in xrange(q):
    Q.append((randint(1, n + 1), randint(1, n + 1), randint(1, n + 1)))

TE = set()
for u, v in E:
    if u > v:
        u, v = v, u
    if u == v:
        continue
    TE.add((u, v))

E = list(TE)
shuffle(E)
shuffle(Q)

print n + 1, len(E), q
for u, v in E:
    print u, v

Q = Q[:q]
for u, v, t in Q:
    print u, v, t
