#!/usr/bin/env pypy

from sys import argv
from random import *

n, L = map(int, argv[1:])

print n, 3, L

P = range(1, n + 1)
shuffle(P)

for i in xrange(0, n - 1):
    print P[i], P[i + 1]
