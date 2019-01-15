#!/usr/bin/env pypy

from random import *
from sys import *

T, n, CMAX = map(int, argv[1:])
print T
for t in xrange(T):
    print n
    G = [[0] * n for i in xrange(n)]
    for i in xrange(n):
        for j in xrange(i + 1, n):
            G[i][j] = G[j][i] = randint(1, CMAX)
    for i in xrange(n):
        print ' '.join(map(str, G[i]))
