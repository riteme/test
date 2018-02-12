#!/usr/bin/env pypy

from sys import *
from random import *

n = int(argv[1])

print n, 1000000000, 1
for i in xrange(2, n + 1):
    u = randint(1, i - 1)
    print i - 1, i