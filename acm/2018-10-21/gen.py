#!/usr/bin/env pypy

from random import *
from sys import *

n, c = map(int, argv[1:])
a = randint(1, n - 1)
b = n - 1 - a
E = []
for i in xrange(2, a + 2):
    E.append("%s %s %s" % (1, i, randint(0, 1)))
for i in xrange(2, a + 2):
    for j in xrange(a + 2, n + 1):
        if randint(1, c) == 1:
            E.append("%s %s %s" % (i, j, randint(0, 1)))

print n, len(E)
print "\n".join(E)
