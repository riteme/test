#!/usr/bin/env pypy

from sys import argv
from random import *

n, m, CMAX = map(int, argv[1:])

assert m <= n * (n - 1) / 2

if m < 0:
    m = n * (n - 1) / 2

print n, m
E = []
for i in xrange(1, n + 1):
    for j in xrange(i + 1, n + 1):
        E.append((i, j, randrange(0, CMAX)))

shuffle(E)
for j in xrange(0, m):
    print "%s %s %s" % E[j]
