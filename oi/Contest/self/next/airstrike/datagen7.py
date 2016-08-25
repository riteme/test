#!/usr/bin/env pypy

import polygon

from random import *

N = 1000
P = [
    (randint(0, 10**3), randint(0, 10**3))
    for i in range(0, N)
]

P = polygon.construct(P)

print("\n".join(
    ["%s %s" % p for p in P]
))
