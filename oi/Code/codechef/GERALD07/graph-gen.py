#!/usr/bin/env python3

from random import *

N = 200
M = 1800
Q = 200

print("1")
print("%s %s %s" % (N, M, Q))

for i in range(0, M):
    u = randint(1, N)
    v = randint(1, N)

    print("%s %s" % (u, v))

print("")

for i in range(0, Q):
    l = randint(1, M)
    r = randint(l, M)

    print("%s %s" % (l, r))
