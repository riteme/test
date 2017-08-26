#!/usr/bin/env pypy

from os import system as sh

N = [4, 10, 13, 20, 48, 100, 199, 297, 356, 477, 500, 892, 998, 1397, 1452, 1823, 1897, 1943, 2000, 1998]
D = [1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]

for i, (n, d) in enumerate(zip(N, D), start=1):
    print "(info) Generating 'sequence%s.in'..." % i
    sh("./gen.py %s %s > sequence%s.in" % (n, d, i))
    print "(info) Generating 'sequence%s.ans'..." % i
    sh("./std < sequence%s.in > sequence%s.ans" % (i, i))
