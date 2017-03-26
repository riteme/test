#!/usr/bin/env pypy

import sys
from random import *

n = int(sys.argv[1])
PMAX = int(sys.argv[2])
VMAX = int(sys.argv[3])

p = randint(1, PMAX)
print n, p
for v in range(2, n + 1):
    # u = randrange(1, v)
    u = v - 1
    print u, v

VAL = []
for i in range(0, n):
    VAL.append(str(randint(0, VMAX)))
print " ".join(VAL)
