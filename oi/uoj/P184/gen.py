#!/usr/bin/env pypy

import sys
from random import *

n = int(sys.argv[1])
m = int(sys.argv[2])
q = int(sys.argv[3])
CMAX = int(sys.argv[4])

print n, m
for i in range(0, n):
    print " ".join([str(randint(1, CMAX)) for i in range(0, m - 1)])
for i in range(0, n - 1):
    print " ".join([str(randint(1, CMAX)) for i in range(0, m)])

print q
for i in range(0, q):
    print randint(1, n), randint(1, m), randint(1, n), randint(1, m)
