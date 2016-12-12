#!/usr/bin/env python3

from random import *

N = 8
M = 14
WMAX = 10

print("%s %s" % (N, M))
for i in range(0, M):
    u = randint(1, N)
    v = randint(1, N)
    w = randint(1, WMAX)

    print("%s %s %s" % (u, v, w))
