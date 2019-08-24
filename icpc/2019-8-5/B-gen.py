#!/usr/bin/pypy

from sys import *
from random import *

T, n = map(int, argv[1:])

print T
for i in xrange(T):
    print n
    print ' '.join(str(randrange(0, 2**30)) for j in xrange(n))
    print ' '.join(str(randrange(0, 2**30)) for j in xrange(n))
