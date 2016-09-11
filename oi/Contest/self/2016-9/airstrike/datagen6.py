#!/usr/bin/env pypy

P = []

N = 250000

sx = -250150
sy = -231
for i in range(0, N):
    P.append((sx + i, sy - i))

sx = 233
sy = -250100
for i in range(0, N):
    P.append((sx + i, sy + i))

sx = 250200
sy = 0
for i in range(0, N):
    P.append((sx - i, sy + i))

sx = -100
sy = 250010
for i in range(0, N):
    P.append((sx - i, sy - i))

print("\n".join(
    ["%s %s" % p for p in P]
))
