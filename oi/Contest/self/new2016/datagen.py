#!/usr/bin/env pypy

import sys

from random import *

if len(sys.argv) < 5:
    print("Usage: %s [N] [CMAX] [L] [R]" % sys.argv[0])
    exit(-1)

N = int(sys.argv[1])
CMAX = int(sys.argv[2])
L = int(sys.argv[3])
R = int(sys.argv[4])
K = randint(1, N * CMAX)

print("%s %s %s %s" % (N, K, L, R))
print(" ".join([str(randint(0, CMAX)) for i in range(0, N)]))
