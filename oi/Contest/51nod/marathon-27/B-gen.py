#!/usr/bin/env pypy

from sys import *
from random import *

n = int(argv[1])

print n
for v in xrange(2, n + 1):
    u = randint(max(1, v - 10), v - 1)
    print u, v
