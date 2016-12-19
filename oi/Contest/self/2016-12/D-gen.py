#!/usr/bin/env pypy

from random import *

N = 300
M = 300
Q = randint(1, N)
W = [str(i) for i in range(1, N + 1)]
shuffle(W)

print("%s %s %s" % (N, M, Q))
print(" ".join(W))

for i in range(2, N + 1):
    father = randint(1, i - 1)

    print("%s %s" % (father, i))

for i in range(0, M):
    opt = randint(0, 1)
    u = randint(1, N)
    v = randint(1, N)

    print("%s %s %s" % (opt, u, v))
