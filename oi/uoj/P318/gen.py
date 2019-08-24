#!/usr/bin/env pypy

from sys import argv
from random import *

n, m, Q, WMAX, C1MAX, C2MAX = map(int, argv[1:])

print n, Q, m
for i in xrange(n):
    c = randint(1, C1MAX)
    print randint(1, WMAX),randint(1, WMAX), c, randint(0, min(c, C2MAX))
print "\n".join(map(str, range(1, m + 1)))
