#!/usr/bin/python2

from random import *

T = 5
n = 1000
m = 10000

print T
for t in xrange(T):
    print n, m
    for i in xrange(m):
        u = randint(1, n)
        v = randint(1, n)
        while u == v:
            v = randint(1, n)
        print u, v, randint(1, 1000)