#!/usr/bin/env pypy

from sys import argv
from random import *

n, CMAX = map(int, argv[1:])

print n, randint(1, n)
for i in xrange(n):
    print randint(-CMAX, CMAX), randint(-CMAX, CMAX)
