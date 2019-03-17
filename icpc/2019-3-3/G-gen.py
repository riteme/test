#!/usr/bin/env pypy

from sys import *
from random import *

n, hMin, hMax, z, yMin, yMax = map(int, argv[1:])
print n, randint(hMin, hMax)
P = sorted(sample(range(1, z + 1), n))
for p in P:
    print p, randint(yMin, yMax)

