#!/usr/bin/env pypy

from random import *
from sys import *

n = int(argv[1])
print 1, n
for i in xrange(2, n + 1):
    print randint(1, i - 1), i
