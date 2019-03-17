#!/usr/bin/env pypy

from sys import *
from random import *

n, m, wMin, wMax = map(int,argv[1:])

print n, m, randint(1, n)
for i in xrange(m):
    print randint(1, n), randint(1, n), randint(wMin, wMax)
