#!/usr/bin/pypy

from sys import *
from random import *

n, m, q, K, C = map(int, argv[1:])

print n, m
# for v in xrange(2, n + 1):
#     u = randint(1, v - 1)
#     w = randint(1, C)
#     print u, v, w
# m -= n - 1

for i in xrange(m):
    u = randint(1, n)
    v = randint(1, n)
    w = randint(1, C)
    print u, v, w

print q
for i in xrange(q):
    s = randint(1, n)
    t = randint(1, n)
    k = randint(0, K)
    idx = [randint(1, m) for j in xrange(k)]
    print s, t, k, ' '.join(map(str, idx))