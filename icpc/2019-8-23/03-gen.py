#!/usr/bin/pypy

from sys import *
from random import *

T, n, q = map(int, argv[1:])

print T
for t in xrange(T):
    print n, q
    S = 'abcd'
    print ''.join(choice(S) for i in xrange(n))
    for i in xrange(q):
        l = randint(1, n)
        r = randint(l, n)
        k = randint(1, 10)
        print l, r, k
