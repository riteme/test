#!/usr/bin/env pypy

import sys
from random import *

if len(sys.argv) < 3:
    print "Usage: ", sys.argv[0], " [N] [M]"
    exit(-1)

n = int(sys.argv[1])
m = int(sys.argv[2])
CMAX = 100

print n, m
assert m >= n - 1
for v in range(2, n + 1):
    u = randrange(1, v)
    w = randint(1, CMAX)

    print u, v, w

for i in range(0, m - n + 1):
    u = randint(1, n)
    v = randint(1, n)
    w = randint(1, CMAX)

    print u, v, w

