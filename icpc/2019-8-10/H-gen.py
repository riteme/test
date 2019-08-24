#!/usr/bin/pypy

from sys import *
from random import *

n, m, q, M0, S0 = map(int, argv[1:])

print n, m, q
S = 'abcdefghijklmnopqrstuvwxyz'
for i in xrange(2, n + 1):
    u = randrange(1, i)
    #s = sample(S, randint(1, S0))
    s = sample(S, S0)
    print u, i, ''.join(s)
for i in xrange(m):
    #print ''.join(choice(S) for j in xrange(randint(1, M0)))
    print ''.join(choice(S) for j in xrange(M0))
for i in xrange(q):
    u = randint(1, n - 1)
    v = randint(u + 1, n)
    if randint(0, 1):
        u, v = v, u
    print u, v
