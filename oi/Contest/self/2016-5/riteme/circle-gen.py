#!/usr/bin/env pypy

import sys

from random import choice, randint, shuffle

if len(sys.argv) < 3:
    print("Usage: {} [N] [M]".format(sys.argv[0]))
    exit(-1)

N = int(sys.argv[1])
M = int(sys.argv[2])
CMAX = 10
MAX_USED = 4
RANGE = 100

print("%s %s" % (N, M))

V = [1]
E = []
center = 1
used = 0
for i in range(2, N + 1):
    if used >= MAX_USED:
        center = choice(V[max(0, len(V) - RANGE):])
        used = 0
    V.append(i)
    E.append((center, i))
    used += 1
    print("%s %s %s" % (center, i, randint(0, CMAX)))

for i in range(0, M):
    u, v = choice(E)
    print("%s %s %s" % (u, v, randint(0, CMAX)))
