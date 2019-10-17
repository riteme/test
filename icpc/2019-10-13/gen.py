#!/usr/bin/python

from sys import *
from math import *
from random import *

n, m, q = map(int, argv[1:])
S = int(log(n, 2))
L = [randint(1, m) for i in xrange(n)]
#for i in xrange(0, int(n / S) + 1):
#    L.append(1)
#    for j in xrange(1, S + 1):
#        L.append(j * (S - 2))
n = len(L)
print n, 200000, q
print " ".join(map(str, L))
for i in xrange(q):
    l = randint(1, n)
    r = randint(l, n)
    print l, r, randint(1, m)
