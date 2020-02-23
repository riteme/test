#!/usr/bin/python

from sys import *
from random import *

n, m, CMAX, EMAX = map(int, argv[1:])

print n, m, randint(max(EMAX / 2, 1), EMAX)
for i in xrange(m):
    print randint(1, n), randint(1, n), randint(1, CMAX)