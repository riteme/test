#!/usr/bin/pypy

from sys import *
from random import *

T, n, m, q, CMAX = map(int, argv[1:])

print T
for t in xrange(T):
    print n, m, q
    for i in xrange(m):
        u = randint(1, n)
        v = randint(u, n)
        print u, v
    for i in xrange(q):
        print randint(1, CMAX)
