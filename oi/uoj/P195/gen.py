#!/usr/bin/env pypy

from sys import argv
from random import *

n, q = map(int, argv[1:])

print n, q
interval = [None, (1, n)]
OP = [0] * 5 + [1] * 4 + [2] * 3
for i in range(q):
    op = choice(OP)

    if op == 0:
        # l = randint(1, n)
        # r = randint(l, n)
        l, r = 1, n
        interval.append((l, r))
        print 0, l, r
    elif op == 1:
        # l = randint(1, n)
        # r = randint(l, n)
        l, r = 1, n
        x = randrange(1, len(interval))
        print 1, l, r, x
    else:
        x = randint(1, n)
        u, v = randrange(1, len(interval)), randrange(1, len(interval))
        while x < interval[u][0] or x > interval[u][1]:
            u = randrange(1, len(interval))
        while x < interval[v][0] or x > interval[v][1]:
            v = randrange(1, len(interval))

        print 2, x, u, v
