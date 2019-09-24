#!/usr/bin/pypy

from sys import *
from random import *

T, n, m = map(int, argv[1:])
print T
for t in xrange(T):
    print n, m, 998244353
    for i in xrange(m):
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        print u, v
