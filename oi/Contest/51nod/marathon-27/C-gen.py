#!/usr/bin/env pypy

from sys import *
from random import *

T, N, K = map(int, argv[1:])

print T
for i in xrange(T):
    print randint(0, N), randint(1, K)
