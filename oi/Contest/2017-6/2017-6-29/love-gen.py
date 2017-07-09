#!/usr/bin/env pypy

from random import *
from sys import *

n, CMAX = map(int, argv[1:])

print n
for i in xrange(n):
    a = randint(1, CMAX)
    b = randint(1, CMAX)
    print a, a, b, b
