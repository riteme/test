#!/usr/bin/env pypy

from sys import *
from random import *

n, m, L, q, v = map(int, argv[1:])

u = randint(1, v - 1)

print n, m, q, u, v, 1
print " ".join(map(str, sorted([randint(0, L) for i in xrange(n)], key = lambda x : -x)))
