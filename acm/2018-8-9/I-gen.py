#!/usr/bin/env pypy

from math import log
from random import *
from sys import argv

n = int(argv[1])

print n
for i in xrange(2, n + 1):
    print randint(1, i - 1), i
print randint(1, 1 + int(log(n, 2)))
