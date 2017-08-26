#!/usr/bin/env pypy

from sys import argv
from random import *

n, CMAX = map(int, argv[1:])

print n
for i in xrange(n):
    print randint(1, CMAX), randint(-CMAX, -1), randint(1, CMAX)
