#!/usr/bin/python

from sys import *
from random import *

n, m = map(int, argv[1:])

print n, m
for i in xrange(n):
    r = randint(1, m)
    l = randint(r - m + 1, r)
    print l, r
