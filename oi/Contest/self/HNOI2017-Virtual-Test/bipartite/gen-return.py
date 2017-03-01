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
OP = ["ADD", "DEL"]

A = []
pos = 1
while pos <= q:
    op = choice(OP)

    if op == "DEL":
        if len(A) == 0:
            continue;

        u = A.pop();
        print "DEL", u
    else:
        u, v = randint(1, n), randint(1, n)
        A.append(pos)
        print "ADD", u, v

    pos += 1
