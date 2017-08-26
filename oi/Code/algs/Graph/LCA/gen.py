#!/usr/bin/env pypy

from sys import *
from random import *

n, q = map(int, argv[1:])

print n, q

fa = []
for v in xrange(2, n + 1):
    fa.append(randint(max(1, v - 20), v - 1))

print " ".join(map(str, fa))

for i in xrange(q):
    print randint(1, n), randint(1, n)
