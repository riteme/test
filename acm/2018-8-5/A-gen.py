#!/usr/bin/env pypy

from random import *
from sys import argv

n, m, d = map(int, argv[1:])
print d, n, m
for i in xrange(m):
    print randint(1, n), randint(1, n), randint(1, d)
