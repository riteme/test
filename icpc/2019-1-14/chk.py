#!/usr/bin/env pypy

from sys import *

def readln(stream, f):
    return map(f, stream.readline().split())
def read2lst(stream, f, n):
    return map(lambda x : [0] + list(x), zip(*(readln(stream, f) for i in xrange(n))))

with open("data.in", "r") as reader:
    n, m = readln(reader, int)
    L, R = read2lst(reader, int, n)
    P, S = read2lst(reader, int, m)
with open(argv[1], "r") as reader:
    seq = [int(reader.readline()) for i in xrange(n)]
    pos = [0] * (n + 1)
    for i, j in enumerate(seq, start=1):
        pos[j] = i
ok = True
for i in xrange(1, n + 1):
    ok &= L[i] <= pos[i] <= R[i]
for i in xrange(m):
    ok &= pos[P[i]] <= pos[S[i]]
exit(0 if ok else 1)
