#!/usr/bin/pypy

from sys import *
from random import *

T, n, m, Kl, Kr = map(int, argv[1:])

def randbits(n):
    return ''.join((choice('01') for i in xrange(n)))

print T
for i in xrange(T):
    k = randint(Kl, Kr)
    l = randint(1, (n * k + 1) / 2)
    r = randint((l + n * k) / 2, n * k + 1)
    print n, k, m, l, r
    print '1' + randbits(n)
    print randbits(m)
