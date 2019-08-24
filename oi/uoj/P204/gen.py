#!/usr/bin/env pypy

import sys
from random import *

n = int(sys.argv[1])

print n
for i in range(0, n):
    l = randint(1, 10**9)
    r = randint(l, 10**9)
    print l, r
