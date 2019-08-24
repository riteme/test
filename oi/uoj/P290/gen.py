#!/usr/bin/pypy

from sys import *
from random import *

n, m, K = map(int, argv[1:])
# n: tree size
# m: cycle count
# K: argument for cycle size

E = []
for i in xrange(2, n + 1):
    E.append((randrange(1, i), i))
for i in xrange(n - 2, n - 2 - m, -1):
    j = randint(0, i)
    E[i], E[j] = E[j], E[i]
    s = randint(1, K - 2)
    u, v = E[i]
    E.append((u, n + 1))
    for k in xrange(n + 1, n + s):
        E.append((k, k + 1))
    E.append((n + s, v))
    n += s
print 1
print n, len(E)
print '\n'.join(('%s %s' % e for e in E))
