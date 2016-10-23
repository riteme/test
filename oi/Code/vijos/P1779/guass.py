#!/usr/bin/env python

# Strange conclusion......
# I don't feel like writing MP.

n = int(raw_input())
A, B = [int(x) for x in raw_input().split(" ")]
L = []
for i in range(0, n):
    a, b = [int(x) for x in raw_input().split(" ")]
    L.append((a, b))

L = sorted(L, key = lambda x : x[0] * x[1])
pre = A
answer = -1
for a, b in L:
    answer = max(answer, int(pre / b))
    pre *= a

print(answer)
