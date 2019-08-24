#!/usr/bin/env python3

from random import *

NMAX = 1000
XMAX = 10000
YMAX = 10000
S = set()

while len(S) < NMAX:
    S.add((randint(-XMAX, XMAX), randint(-YMAX, YMAX)))

L = ["%s %s" % x for x in S]
print(NMAX)
print("\n".join(L))
