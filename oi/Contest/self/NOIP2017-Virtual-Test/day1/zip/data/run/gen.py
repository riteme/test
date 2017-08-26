#!/usr/bin/env pypy

from sys import *
from random import *

n, m, CMAX = map(int, argv[1:])

print n, n + m

P = range(1, n + 1)
E = set()

def add(u, v):
    if u > v:
        u, v = v, u
    E.add((u, v))

shuffle(P)
for i in xrange(n):
    if i < n - 1:
        add(P[i], P[i + 1])
    else:
        add(P[i], P[0])

while len(E) < n + m:
    u = randint(1, n)
    v = randint(1, n)
    while u == v:
        v = randint(1, n)
    add(u, v)

E = list(E)
shuffle(E)
for u, v in E:
    print u, v, randint(1, CMAX)
