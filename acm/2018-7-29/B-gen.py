#!/usr/bin/env pypy

from random import *
from sys import argv

n, CMAX, RMAX = map(int, argv[1:])

print n
for i in xrange(n):
    print randint(1, CMAX), randint(1, CMAX), randint(1, RMAX)
