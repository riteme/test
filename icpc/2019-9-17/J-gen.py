#!/usr/bin/pypy

from sys import *
from random import *

T, n, m = map(int, argv[1:])

print T
for t in xrange(T):
    print n, m
    for i in xrange(n):
        xl = randint(1, m)
        xr = randint(xl, m)
        yl = randint(1, m)
        yr = randint(yl, m)
        print xl, xr, yl, yr
