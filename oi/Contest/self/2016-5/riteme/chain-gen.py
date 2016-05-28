#!/usr/bin/env pypy

import sys

from random import choice, randint, shuffle

if len(sys.argv) < 3:
    print("Usage: {} [N] [M]".format(sys.argv[0]))
    exit(-1)

N = int(sys.argv[1])
M = int(sys.argv[2])
CMAX = 10

print("%s %s" % (N, M))
for i in range(1, N):
    print("%s %s %s" % (i, i + 1, randint(0, CMAX)))

for i in range(0, M):
    v = randint(2, N)
    print("%s %s %s" % (v - 1, v, randint(0, CMAX)))
