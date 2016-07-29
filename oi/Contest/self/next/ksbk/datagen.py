#!/usr/bin/env pypy

import sys

from random import *

if len(sys.argv) < 3:
    print("Usage: %s [N] [K]" % sys.argv[0])
    exit(-1)

N = int(sys.argv[1])
K = int(sys.argv[2])

print("%s %s" % (N, K))

L = [str(i) for i in range(1, N + 1)]
shuffle(L)
print(" ".join(L))
shuffle(L)
print(" ".join(L))
