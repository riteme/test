#!/usr/bin/env pypy

import itertools

S = []
for i in xrange(7):
    S += [i] * 2

s = 0
cnt = 0
for c in itertools.combinations(S, 4):
    cnt += 1
    marked = [0] * 7
    for a in c:
        marked[a] = 1
    s += sum(marked)

print float(s) / cnt
