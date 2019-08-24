#!/usr/bin/env pypy

import sys

from random import *

if len(sys.argv) < 4:
    print("Usage: %s [N] [M] [C]" % sys.argv[0])
    exit(-1)

N = int(sys.argv[1])
M = int(sys.argv[2])
C = int(sys.argv[3])

print("%s %s" % (N, M))

for i in range(2, N + 1):
    print("%s %s" % (randrange(1, i), i))

cnt = 0
types = [0, 0, 1, 2, 2]
paths = []

while cnt < M:
    t = choice(types)

    if t == 0:
        cnt += 1
        u = randint(1, N)
        v = randint(1, N)
        w = randint(0, C)
        paths.append(cnt)

        print("0 %s %s %s" % (u, v, w))

    elif t == 1:
        if len(paths) > 0:
            cnt += 1
            idx = choice(paths)
            paths.remove(idx)

            print("1 %s" % idx)

    elif t == 2:
        cnt += 1
        idx = randint(1, N)

        print("2 %s" % idx)
