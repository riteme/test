#!/usr/bin/env pypy

from sys import *
from random import *

n, m, q = map(int, argv[1:])

print n, m, q
for i in xrange(m):
    print randint(1, n), randint(1, n)
for i in xrange(q):
    print randint(1, n), randint(1, n), randint(1, n)
