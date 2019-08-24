#!/usr/bin/env pypy

import sys
from random import *

if len(sys.argv) < 2:
    print("Usage: %s [N]" % sys.argv[0])
    exit(-1)

n = int(sys.argv[1])

print("%s 0" % n)

for u in range(2, n + 1):
    father = randrange(1, u)
    distance = randint(1, 2 * 10**5)
    per = randint(0, 10**6)
    init = randint(0, 10**12)
    length = randint(distance, 3 * 10**5)

    print("%s %s %s %s %s" % (father, distance, per, init, length))
