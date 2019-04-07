#!/usr/bin/pypy

from sys import *
from random import *

T, n, m, K = map(int, argv[1:])
print T
for i in xrange(T):
    print n, m
    for j in xrange(m):
        l = randint(1, n)
        r = randint(l, min(n, l + K - 1))
        print l, r
