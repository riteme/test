#!/usr/bin/env pypy

from random import *

NMAX = 10**9
MMAX = 5000
CMAX = 1

for m in range(2, MMAX + 1):
    for c in range(0, CMAX):
        n = randint(1, NMAX)

        print("{} {}".format(n, m))
