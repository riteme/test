#!/usr/bin/pypy

from sys import *
from random import *

n, m, W, H = map(int, argv[1:])
print n, m, W, H
P = set()
while len(P) < n:
    P.add((randint(1, W), randint(1, H)))
P = list(P)
shuffle(P)
print '\n'.join('%s %s' % p for p in P)
for i in xrange(m):
    L = randint(1, W)
    R = randint(L, W)
    D = randint(1, H)
    U = randint(D, H)
    print randint(1, n), 10000, L, R, D, U
