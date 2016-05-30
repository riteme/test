#!/usr/bin/env pypy

import sys

if len(sys.argv) < 2:
    print("Usage: %s [N]" % (sys.argv[0], ))
    exit(-1)

N = int(sys.argv[1])

for i in range(4, N + 1, 4):
    print("%s %s %s %s" % (i, i - 2, i - 3, i - 1))
