#!/usr/bin/env pypy

from sys import argv
from random import *

n, CMAX = map(int, argv[1:])

print n

for i in xrange(n):
    l = randint(1, n - 1)
    r = randint(l, n - 1)
    print l, r

for v in xrange(2, n + 1):
    u = randrange(1, v)
    w = randint(0, CMAX)
    print u, w
