#!/usr/bin/env pypy

import sys
from random import randint, choice, shuffle

if len(sys.argv) < 2:
    print("Usage: %s [N]" % (sys.argv[0], ))
    exit(-1)

N = int(sys.argv[1])

seq = [x for x in range(1, N + 1)]
shuffle(seq)

for i in seq:
    print("%s" % (i, ))
