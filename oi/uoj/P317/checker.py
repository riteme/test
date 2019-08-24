#!/usr/bin/env pypy

from sys import *

inp, out = argv[1:]

L = []
with open(inp, 'r') as reader:
    n, d = map(int, reader.readline().split())
    mask = ' ' + reader.readline()
    q = int(reader.readline())

    for i in xrange(q):
        a, b, c, d = reader.readline().split()
        L.append((int(a), b, int(c), d))

with open(out, 'r') as reader:
    ans = ' ' + reader.readline()

for i in xrange(1, n + 1):
    if mask[i].upper() == ans[i]:
        print "Map %s can't use car %s." % (i, ans[i])
        exit(-1)

for i, (a, b, c, d) in enumerate(L):
    if ans[a] == b and ans[c] != d:
        print "Map %s must use car %s, required by R%s [%s %s %s %s]." % (c, d, i + 1, a, b, c, d)
        exit(-2)
