#!/usr/bin/env pypy

import sys
from random import *

if len(sys.argv) < 2:
    print("Usage: %s [N]" % sys.argv[0])
    exit(-1)

DMAX = 10**4
RMAX = 10**9

n = int(sys.argv[1])
print(0)
print(n)
for i in range(1, n + 1):
    u = i - 1
    d = 0
    r = randint(1, RMAX)

    if i > 1:
        d = randint(1, DMAX)

    print("%s %s %s" % (u, d, r))
