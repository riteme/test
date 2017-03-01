#!/usr/bin/env pypy

import sys

if len(sys.argv) < 3:
    print "Usage: %s [INPUT] [ANSWER]" % sys.argv[0]
    exit(-1)

inp = sys.argv[1]
ans = sys.argv[2]

def readline(io):
    return [int(x) for x in io.readline().split()]

reader = open(inp, "r")
n, q, s = readline(reader)
OP = []
for i in range(0, q):
    OP.append(reader.readline())
reader.close()

reader = open(ans, "r")
xcnt, ycnt = 0, 0
xpre = [0] * q
ypre = [0] * q
for i in range(0, q):
    word = reader.readline()

    if word.strip() == "YES":
        xcnt += 1
    else:
        ycnt += 1

    xpre[i], ypre[i] = xcnt, ycnt
reader.close()

print n, q, 1
for i, op in enumerate(OP):
    if op.startswith("ADD"):
        s, u, v = op.split()

        if i > 0:
            u = int(u) ^ (xpre[i - 1] | ypre[i - 1])
            v = int(v) ^ (xpre[i - 1] | ypre[i - 1])

        print "ADD", u, v
    else:
        print op.strip()
