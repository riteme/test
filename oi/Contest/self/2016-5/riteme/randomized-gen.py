#!/usr/bin/env pypy

import sys

from random import choice, randint, shuffle

if len(sys.argv) < 3:
    print("Usage: {} [N] [M]".format(sys.argv[0]))
    exit(-1)

N = int(sys.argv[1])
M = int(sys.argv[2])
CMAX = 10
RANGE = 100

print("%s %s" % (N, M))

V = [1]
E = []
for i in range(2, N + 1):
    u = choice(V[max(0, len(V) - RANGE):])
    V.append(i)
    E.append((u, i))
    print("%s %s %s" % (u, i, randint(0, CMAX)))

for i in range(0, M):
    u, v = choice(E)
    print("%s %s %s" % (u, v, randint(0, CMAX)))
