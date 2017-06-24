#!/usr/bin/env pypy

from sys import argv
from random import *

n, m, t = map(int, argv[1:])

print n, m
mat = [['.'] * m for i in xrange(n)]

for i in xrange(t):
    x, y = randrange(0, n), randrange(0, m)
    mat[x][y] = '*'

for i in xrange(n):
    print "".join(mat[i])
