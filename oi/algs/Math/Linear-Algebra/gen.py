#!/usr/bin/env pypy

from random import *
from sys import *

n, m, RMAX = map(int, argv[1:])

print n, m
for v in xrange(2, n + 1):
    u = randrange(1, v)
    print("%s %s %.2lf" % (u, v, uniform(0, RMAX)))

for i in xrange(m - n + 1):
    print("%s %s %.2lf" % (randint(1, n), randint(1, n), uniform(0, RMAX)))
