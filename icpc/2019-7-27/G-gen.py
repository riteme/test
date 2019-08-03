#!/usr/bin/env pypy

from sys import *
from random import *

n, q, m0 = map(int, argv[1:])
print n
for i in xrange(2, n + 1):
    print randint(1, i - 1), i
print q
for i in xrange(q):
    m = randint(1, m0)
    print m
    for j in xrange(2, m + 1):
        print randint(1, j - 1), j
