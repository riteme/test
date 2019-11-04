#!/usr/bin/python3

from sys import *
from random import *

n, q, S, K, L = map(int, argv[1:])
Σ = "ABCDEFGHIJKLMOPQRSTUVWXYZ"[:S]

print(n, q)
print(''.join((choice(Σ) for i in range(n))))

depth = [0, 1]
father = []
for v in range(2, n + 1):
    u = randint(max(1, v - L), v - 1)
    father.append(u)
    depth.append(depth[u] + 1)
print(' '.join(map(str, father)))

for i in range(q):
    x = randint(1, n)
    l = randint(1, min(K, depth[x]))
    print(x, l)
