#!/usr/bin/env pypy

from sys import *
from random import *

n = int(argv[1])
print n, randint(1, n / 1000 - 1)
for i in xrange(2, n + 1):
    print randint(max(1, i - 10), i - 1), i, randint(-10**6, 10**6)
