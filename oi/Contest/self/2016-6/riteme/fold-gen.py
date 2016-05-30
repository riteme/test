#!/usr/bin/env pypy

import sys

if len(sys.argv) < 2:
    print("Usage: %s [N]" % (sys.argv[0], ))
    exit(-1)

N = int(sys.argv[1])

for i in range(N / 2, 0, -1):
    print("%s" % (i, ))
for i in range(N / 2 + 1, N + 1):
    print("%s" % (i, ))
