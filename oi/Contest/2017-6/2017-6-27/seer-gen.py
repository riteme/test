#!/usr/bin/env pypy

from sys import argv
from random import *

n, m, K = map(int, argv[1:])

print n, m, K

if n == m:
    for i in xrange(1, n):
        print i, i + 1
    print n, 1
else:
    for i in xrange(m):
        u = randint(1, n - 1)
        v = randint(u + 1, n)
        print u, v
