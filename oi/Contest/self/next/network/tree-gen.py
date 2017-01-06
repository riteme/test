#!/usr/bin/env pypy

import sys
from random import *

N = int(sys.argv[1])
S = [i for i in xrange(1, N + 1)]
shuffle(S)
E = []
for i in xrange(1, N):
    E.append((choice(S[:i]), S[i]))
shuffle(E)

print("%s %s" % (N, N - 1))
for e in E:
    print("%s %s %s" % (e[0], e[1], N))
