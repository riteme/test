#!/usr/bin/env pypy

import sys
from random import *

n = int(sys.argv[1])
CMAX = int(sys.argv[2])

print 2, n
for i in range(0, n):
    print 'A', randint(0, CMAX), 'B', randint(0, CMAX)
