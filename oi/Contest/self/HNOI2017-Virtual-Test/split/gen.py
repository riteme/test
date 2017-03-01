#!/usr/bin/env pypy

import sys
from random import *

if len(sys.argv) < 6:
    print "Usage: %s [N] [M] [CMAX] [WMAX] [MONEYMAX]" % sys.argv[0]
    exit(-1)

n = int(sys.argv[1])
m = int(sys.argv[2])
CMAX = int(sys.argv[3])
WMAX = int(sys.argv[4])
MMAX = int(sys.argv[5])

print n, m, randint(0, MMAX)
for i in range(1, n + 1):
    line = []
    for j in range(1, m):
        line.append("%s %s" % (randint(1, CMAX), randint(WMAX / 2, WMAX)))

    print " ".join(line)

for i in range(1, n):
    line = []
    for j in range(1, m + 1):
        line.append("%s %s" % (randint(1, CMAX), randint(WMAX / 2, WMAX)))

    print " ".join(line)
