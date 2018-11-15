#!/usr/bin/env pypy

from sys import argv
from random import *

n, m, k, CMAX = map(int, argv[1:])

print n, m, k

for i in xrange(k):
    print randint(1, CMAX * 100), -1
for i in xrange(n - 1):
    for j in xrange(k):
        print -1, randint(1, CMAX * 100)

E = set()
while len(E) < m:
    u = randint(1, n)
    v = randint(1, n)
    while u == v:
        v = randint(1, n)

    E.add((u, v))

for e in E:
    print "%s %s %s" % (e[0], e[1], randint(1, CMAX))
