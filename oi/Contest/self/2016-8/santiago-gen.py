#!/usr/bin/env pypy

from random import *

NMAX = 6
MMAX = 6

P = [0, 0, 0, 1, 1, 1, 1, 1, 1, 1]

print("%s %s" % (NMAX, MMAX))
print("\n".join([
    "".join([
        str(choice(P))
        for j in range(0, MMAX)
    ])
    for i in range(0, NMAX)
]))
