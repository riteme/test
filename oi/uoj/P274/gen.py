#!/usr/bin/env pypy

from sys import *
from random import *

n, q, CMAX = map(int, argv[1:])

print n, q

ecnt = 0
P = set()
while len(P) < q:
    P.add(randint(1, CMAX))

while q:
    op = choice(['find', 'move', 'change'])

    if op == 'find':
        print op, ecnt, randint(0, n - 1), randint(0, n - 1), P.pop(), randint(1, CMAX)
        ecnt += 1
        q -= 1
    elif op == "move":
        print op, randint(0, n - 1), randint(0, n - 1)
        q -= 1
    elif op == "change":
        if ecnt > 0:
            print op, randint(0, ecnt - 1), randint(1, CMAX)
            q -= 1
