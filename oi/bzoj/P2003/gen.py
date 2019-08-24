#!/usr/bin/env pypy

import sys
from random import *

n = int(sys.argv[1])
m = int(sys.argv[2])
q = int(sys.argv[3])

print("%s %s %s" % (n, m, q))

mat = [
    [
        randrange(0, q) for i in xrange(0, m)
    ]
    for i in xrange(0, n)
]

for i in xrange(n - 1, 0, -1):
    for j in xrange(m - 1, 0, -1):
        mat[i][j] += mat[i - 1][j] + mat[i][j - 1] + mat[i - 1][j - 1]

for i in xrange(0, n):
    mat[i][0] = 0
for i in xrange(0, m):
    mat[0][i] = 0

for line in mat:
    print(" ".join([str(x) for x in line]))
