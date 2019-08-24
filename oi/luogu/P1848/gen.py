#!/usr/bin/env pypy

from sys import *
from random import *

n, L, H = map(int, argv[1:])

print n, L
for i in xrange(n):
    print randint(1, H), randint(1, L)
