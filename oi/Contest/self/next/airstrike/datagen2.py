#!/usr/bin/env pypy

import polygon

from random import *

N = 1000
P = [
    (randint(-2 * 10**8, 2 * 10**8), randint(-2 * 10**8, 2 * 10**8))
    for i in range(0, N)
]

P = polygon.construct(P)

print("\n".join(
    ["%s %s" % p for p in P]
))
