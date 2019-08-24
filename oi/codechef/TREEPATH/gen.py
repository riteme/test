#!/usr/bin/env pypy

from sys import *
from random import *

T, n, Kl, Kr = map(int, argv[1:])
print T
for i in xrange(T):
    print n
    print ' '.join((str(randint(Kl, Kr)) for j in xrange(n)))
    for j in xrange(2, n + 1):
        print randint(1, j - 1), j
