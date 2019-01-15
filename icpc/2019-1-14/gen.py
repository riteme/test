#!/usr/bin/env pypy

from sys import *
from random import *

n, m = map(int, argv[1:])
perm = range(1, n + 1)
shuffle(perm)
perm = [0] + perm
pos = [0] * (n + 1)
for i in xrange(1, n + 1):
    pos[perm[i]] = i
#print perm
#print pos
print n, m
for i in xrange(1, n + 1):
    print randint(1, pos[i]), randint(pos[i], n)
for i in xrange(m):
    u = randint(1, n - 1)
    v = randint(u + 1, n)
    if pos[u] > pos[v]:
        u, v = v, u
    print u, v
