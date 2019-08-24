#!/usr/bin/env python

import sys

from random import *

n = int(sys.argv[1])
w = int(sys.argv[2])
h = int(sys.argv[3])

G = [['A'] * w for i in range(0, h)]
# for i in range(0, h - 1, 2):
#     if i % 4 == 0:
#         for j in range(0, w - 1):
#             G[i + 1][j] = 'x'
#     else:
#         for j in range(1, w):
#             G[i + 1][j] = 'x'

P = set()
while len(P) < n:
    x = randrange(0, h)
    y = randrange(0, w)

    if G[x][y] == 'A':
        P.add((x, y))

P = list(P)
shuffle(P)
for idx, (x, y) in enumerate(P):
    G[x][y] = str(idx + 1)

print n, w, h
for i in range(0, h):
    print "".join(G[i])
