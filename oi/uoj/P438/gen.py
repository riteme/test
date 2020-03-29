#!/usr/bin/python2

from sys import *
from random import *

n, C = map(int, argv[1:])

print n, randint(1, n - 1)
for v in xrange(2, n + 1):
    print randint(1, v - 1), v, randint(1, C)