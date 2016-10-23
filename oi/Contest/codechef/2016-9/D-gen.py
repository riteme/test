#!/usr/bin/env pypy

import itertools

N = 5

V = [i for i in range(1, N + 1)]
E = ["%d %d" % i for i in itertools.combinations(V, 2)]
G = []

for i in range(0, len(E)):
    for S in itertools.combinations(E, i):
        G.append(S)

print(len(G))
for g in G:
    print("%s %s %s" % (N, len(g), " ".join(list(g))))
