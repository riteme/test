#!/usr/bin/env pypy

from random import *

NMAX = 20
CMAX = 40000
S = set()

while len(S) < NMAX:
    S.add(randint(1, CMAX))

print(NMAX)
print("\n".join([str(x) for x in S]))
