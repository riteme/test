#!/usr/bin/pypy

from random import *

T = 500
n = 100
L = 30
for i in xrange(T):
    print n, L
    print ' '.join(str(randint(1, 10**9)) for j in xrange(n))
print 0, 0
