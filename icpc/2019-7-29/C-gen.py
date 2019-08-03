#!/usr/bin/pypy

from sys import *
from random import *

T, n, K0 = map(int, argv[1:])

print T
for i in xrange(T):
    print n, randint(K0 / 10, K0)
    print ''.join(choice("0123456789") for i in xrange(n))
    for j in xrange(2, n + 1):
        print randint(max(1, j - 10), j - 1), j
        #print j - 1, j
    print ''
