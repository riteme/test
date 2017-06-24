#!/usr/bin/env pypy

from sys import argv
from random import *

n = int(argv[1])

print 1
print n, n**2

for i in xrange(n):
    P = range(1, n + 1)
    shuffle(P)

    line = ""
    for x in P:
        line += "0 " * i + str(x) + " " + "0 " * (n - i - 1)
    print line
