#!/usr/bin/env pypy

import sys
from random import *

if len(sys.argv) < 3:
    print("Usage: %s [N] [Q]" % sys.argv[0])
    exit(-1)

N = int(sys.argv[1])
Q = int(sys.argv[2])

print("%s %s" % (N, Q))
for i in range(0, Q):
    u = randint(1, N)
    v = randint(1, N)
    t = randint(1, Q - i)

    print("%s %s %s" % (u, v, t))
