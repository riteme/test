#!/usr/bin/pypy

from sys import *
from random import *

T, n, K0 = map(int, argv[1:])
print T
S = 'ab'
for t in xrange(T):
    print ''.join(choice(S) for i in xrange(n))
    print randint(1, min(K0, n))
