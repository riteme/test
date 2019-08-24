#!/usr/bin/env pypy

from sys import *
from random import *

n = int(argv[1])

print -1000, -1000, 1000, 1000
print n
for i in xrange(n):
    print randint(-1000, 1000), randint(-1000, 1000), 0.5
