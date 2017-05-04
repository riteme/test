#!/usr/bin/env pypy

from sys import argv
from random import *

n, CMAX = map(int, argv[1:])

print n

E = set()
for v in xrange(2, n + 1):
    u = randrange(1, v)
    E.add((u, v))
    print u, v, randint(1, CMAX)

while len(E) < n:
    u = randint(1, n - 1);
    v = randint(u + 1, n)

    if (u, v) in E or (v, u) in E:
        continue

    E.add((u, v))
    print u, v, randint(1, CMAX)
