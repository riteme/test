#!/usr/bin/pypy

from random import *

N = 1000000
M = 1200000
OP = ["Q", "Q", "Q", "Q", "Q", "C", "C", "C", "C", "C", "A"]

print("%s %s" % (N, M))

vermax = 1
for i in range(0, M):
    op = choice(OP)

    if op == 'A':
        v = randint(1, vermax)
        p = randint(1, N)
        x = randint(1, 10)

        print("A %s %s %s" % (v, p, x))
    elif op == 'Q':
        v = randint(1, vermax)
        l = randint(1, N)
        r = randint(l, N)

        print("Q %s %s %s" % (v, l, r))
    else:
        v = randint(1, vermax)
        vermax += 1

        print("C %s" % (v, ))
