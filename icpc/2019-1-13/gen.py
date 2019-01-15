#!/usr/bin/env pypy

from random import *
from sys import *

n, q = map(int, argv[1:])
print n
L = range(0, n)
shuffle(L)
print ' '.join(map(str, L))
print ' '.join(map(str, (randint(1, i - 1) for i in xrange(2, n + 1))))
print q * 2
for i in xrange(q):
    print 1, randint(1, n), randint(1, n)
    print 2
