#!/usr/bin/env pypy

from random import *

n = 150000
q = 750000

print n, q, 0
E = set()
while len(E) < q:
    E.add((randint(1, n / 2 - 1), randint(n / 2, n)))

for e in E:
    print("ADD %s %s" % e)
