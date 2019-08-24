#!/usr/bin/pypy

from sys import *
from random import *

n, q = map(int, argv[1:])
print 1
print n, q
L = range(1, n + 1)
shuffle(L)
print ' '.join(map(str, L))
for i in xrange(q):
    op = randint(1, 2)
    if op == 1:
        print 1, randint(1, n)
    else:
        print 2, randint(1, n), randint(1, n)
