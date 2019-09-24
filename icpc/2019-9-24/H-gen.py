#!/usr/bin/pypy

from sys import *
from random import *

T, n, K = map(int, argv[1:])
print T
for t in xrange(T):
    print n, randint(1, K)
    for i in xrange(n):
        l = randint(0, 10**9 - 1)
        print 100, 200
        r = randint(l + 1, 10**9)
