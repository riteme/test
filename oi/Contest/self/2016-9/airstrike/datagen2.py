#!/usr/bin/env pypy

import polygon

from random import *

N = 1000
P = set()
while len(P) < N:
    P.add((randint(-2 * 10**8, 2 * 10**8), randint(-2 * 10**8, 2 * 10**8)))

P = polygon.construct(list(P))

print("\n".join(
    ["%s %s" % p for p in P]
))
