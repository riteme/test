#!/usr/bin/pypy

from sys import *
from random import *

T, n, C = map(int, argv[1:])
print T
for i in xrange(T):
    K = randint(1, n)
    L = randint(1, K)
    print n, K, L
    print " ".join(map(str, (randint(1, C) for j in xrange(n))))
    print " ".join(map(str, (randint(1, C) for j in xrange(n))))
