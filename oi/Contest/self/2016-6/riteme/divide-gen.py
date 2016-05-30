#!/usr/bin/env pypy

import sys

if len(sys.argv) < 2:
    print("Usage: %s [N]" % (sys.argv[0], ))
    exit(-1)

N = int(sys.argv[1])

seq = [x for x in range(1, N + 1)]
for i in range(1, len(seq) / 2, 2):
    seq[i], seq[len(seq) - i - 1] = seq[len(seq) - i - 1], seq[i]

for x in seq:
    print("%s" % (x, ))
