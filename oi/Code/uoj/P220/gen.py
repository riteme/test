#!/usr/bin/env pypy

from sys import argv
from random import *

n, m = map(int, argv[1:])

print 1
c = 10**5
print n, m, c

P = set()
while len(P) < c:
    P.add((randint(1, n), randint(1, m)))

for x, y in P:
    print x, y
