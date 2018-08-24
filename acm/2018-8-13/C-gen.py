#!/usr/bin/env pypy

from sys import *
from random import *

n, m = map(int, argv[1:])

print n, m
E = set()
for i in xrange(2, n + 1):
    E.add((randint(1, i - 1), i))
while len(E) < m:
    while True:
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        if (u, v) not in E:
            E.add((u, v))
            break

print '\n'.join(('%d %d' % x for x in E))
