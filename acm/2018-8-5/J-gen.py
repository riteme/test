#!/usr/bin/env pypy

from random import *
from sys import argv

n, m, CMAX = map(int, argv[1:])
print n, m
for i in xrange(n):
    l = randint(1, CMAX - 1)
    r = randint(l + 1, CMAX)
    print l, r, randint(1, r - l)
