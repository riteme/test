#!/usr/bin/env pypy

from random import *
from sys import argv

n, m, CMAX = map(int, argv[1:])
print n, m, randint(1, n - 1)
for i in xrange(2, n + 1):
    print randint(1, i - 1), i, randint(1, CMAX)
for i in xrange(m - n + 1):
    print randint(1, n), randint(1, n), randint(1, CMAX)
