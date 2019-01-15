#!/usr/bin/env pypy

from random import *
from sys import *

n = int(argv[1])
print 2 * n
L = []
for i in xrange(1, n + 3):
    L.append(i)
    L.append(i)
L = map(str, L)
shuffle(L)
print ' '.join(L[:2 * n])
shuffle(L)
print ' '.join(L[2:2 * n + 2])
shuffle(L)
print ' '.join(L[4:2 * n + 4])
L = []
for i in xrange(2 * n):
    L.append(str(randint(1, n + 2)))
print ' '.join(L)
