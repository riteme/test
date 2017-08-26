#!/usr/bin/env pypy

from sys import *
from random import *

n, CMAX = map(int, argv[1:])

print n, randint(1, n)
print " ".join(map(str, [randint(1, CMAX) for i in xrange(n)]))
