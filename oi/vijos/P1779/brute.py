#!/usr/bin/env python

import copy
import itertools

n = int(raw_input())
A, B = [int(x) for x in raw_input().split(" ")]
L = []
for i in range(0, n):
    a, b = [int(x) for x in raw_input().split(" ")]
    L.append((a, b))

result = None
for P in itertools.permutations(L):
    pre = A
    answer = 0
    for a, b in P:
        answer = max(answer, int(pre / b))
        pre *= a

    if result is None:
        result = answer
        print(P)
    elif answer < result:
        result = answer
        print(P)

print(result)
