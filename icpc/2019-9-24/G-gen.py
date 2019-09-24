#!/usr/bin/pypy

from sys import *
from random import *

T, n, m = map(int, argv[1:])
print T
for t in xrange(T):
    print n, m, randint(2, m)
    for v in xrange(2, n + 1):
        print randint(1, v - 1), v
    for i in xrange(m):
        print randint(1, n), randint(1, n)
