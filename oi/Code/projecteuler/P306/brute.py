#!/usr/bin/env pypy

import sys

def mex(S):
    S = set(S)
    v = 0
    while v in S:
        v += 1
    return v

n = int(sys.argv[1])

sg = [0] * (n + 1)
cnt = 0

for i in range(2, n + 1):
    S = []
    for j in range(0, i - 1):
        S.append(sg[j] ^ sg[i - j - 2])
    sg[i] = mex(S)

    if sg[i]:
        cnt += 1

print cnt
