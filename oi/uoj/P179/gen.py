#!/usr/bin/env pypy

from sys import argv
from random import *

n, m = map(int, argv[1:])

print n, m, 0
print " ".join([str(randint(-5, 5)) for i in xrange(n)])

for i in xrange(m):
    print " ".join([str(randint(-5, 5)) for i in xrange(n + 1)])
