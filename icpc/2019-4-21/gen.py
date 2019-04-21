#!/usr/bin/pypy

from sys import *
from random import *

n, q, Km, CMAX = map(int, argv[1:])
K = randint(1, Km)
print n, q, K
print ' '.join(map(str, (randint(0, CMAX) for i in xrange(n))))
L = range(1, n + 1)
for i in xrange(q):
    print ' '.join(map(str, sample(L, K)))
