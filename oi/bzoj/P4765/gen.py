#!/usr/bin/env pypy

import sys
from random import *

n = int(sys.argv[1])
q = int(sys.argv[2])
CMAX = int(sys.argv[3])

print n, q
print " ".join([str(randint(0, CMAX)) for i in range(0, n)])
print 0, 1
for i in range(2, n + 1):
    father = randint(1, i - 1)
    print father, i

for i in range(0, q):
    op = randint(1, 2)

    if op == 1:
        u = randint(1, n)
        v = randint(0, CMAX)
        print 1, u, v
    else:
        l = randint(1, n)
        r = randint(l, n)
        print 2, l, r
