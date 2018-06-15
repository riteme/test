#!/usr/bin/env pypy

from sys import argv
from random import *

n, m, CMAX = map(int, argv[1:])

print n, m
for i in xrange(n):
    print randint(0, CMAX), randint(0, CMAX)

for i in xrange(2, n + 1):
    print randint(1, i - 1), i
for i in xrange(m - n + 1):
    print randint(1, n), randint(1, n)
