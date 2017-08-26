#!/usr/bin/env pypy

from random import *

n = 5000

print n
P = range(1, n + 1)
shuffle(P)
print " ".join(map(str, P))
for i in xrange(2, n + 1):
    u = randint(1, i - 1)
    print u, i
