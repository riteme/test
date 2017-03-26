#!/usr/bin/env pypy

import sys
from random import *

n = int(sys.argv[1])
m = int(sys.argv[2])
E = set()
while len(E) < m:
    u = randint(1, n - 1)
    v = randint(u + 1, n)
    E.add("%s %s" % (u, v))

print n, m
for e in E:
    print e
