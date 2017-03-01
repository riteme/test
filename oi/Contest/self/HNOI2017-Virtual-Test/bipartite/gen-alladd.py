#!/usr/bin/env pypy

import sys
from random import *

if len(sys.argv) < 4:
    print "Usage: %s [N] [Q] [S]" % sys.argv[0]
    exit(-1)

n = int(sys.argv[1])
q = int(sys.argv[2])
s = int(sys.argv[3])

print n, q, s

assert q > 10, "q is too small"

S1 = set(sample(range(1, n + 1), n / 2))
S2 = set(range(1, n + 1)) - S1
S1 = list(S1)
S2 = list(S2)
for i in range(0, q - 10):
    u, v = choice(S1), choice(S2)
    print "ADD", u, v

for i in range(0, 5):
    u, v = choice(S1), choice(S1)
    print "ADD", u, v

for i in range(0, 5):
    u, v = choice(S2), choice(S2)
    print "ADD", u, v
