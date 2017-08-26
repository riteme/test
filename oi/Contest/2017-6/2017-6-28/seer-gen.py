#!/usr/bin/env pypy

from sys import argv
from random import *

n, m = map(int, argv[1:])
m = randint(0, m)

print n, m
for i in xrange(m):
    u = randint(1, n - 1)
    v = randint(u + 1, n)
    print u, v
