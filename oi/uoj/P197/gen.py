#!/usr/bin/pypy

from sys import *
from random import *

n, m, K = map(int, argv[1:])
E = [(randrange(1, i), i) for i in xrange(2, n + 1)]
for i in xrange(m):
    idx = randrange(0, len(E))
    u, v = E[idx]
    if randint(0, K):
        E.append((u, v))
    else:
        E[idx], E[-1] = E[-1], E[idx]
        n += 1
        E[-1] = (u, n)
        E.append((n, v))
E = set(E)
print n, len(E)
print '\n'.join(map(lambda x: '%d %d' % x, E))
