#!/usr/bin/env pypy

from sys import *
from random import *

n = int(argv[1])

E = set()
while len(E) < 3 * n / 2:
    u = randint(1, n)
    v = randint(1, n)
    if u > v:
        u, v = v, u
    if u != v:
        E.add((u, v))

print n, len(E)
for u, v in E:
    print u, v
