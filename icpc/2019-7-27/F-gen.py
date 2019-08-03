#!/usr/bin/env pypy

from sys import *
from random import *

n, q = map(int, argv[1:])

print n, q
L = range(1, n + 1)
shuffle(L)
print ' '.join(map(str, L))
for i in xrange(q):
    #l = randint(1, n - 1)
    l = 1
    r = randint(l + 1, n)
    m = randint(l, r - 1)
    print 1, l, m, r
