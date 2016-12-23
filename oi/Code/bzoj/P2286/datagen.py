#!/usr/bin/env pypy

from random import *

N = 250000
WMAX = 100000
KMAX = 10
KALL = 500000

print(N)
for i in range(2, N + 1):
    f = randint(1, i - 1)
    w = randint(1, WMAX)
    
    print("%s %s %s" % (f, i, w))

Q = 0
OP = []
while KALL > 0:
    c = randint(1, KMAX)
    KALL -= c
    S = set()
    while len(S) < c:
        S.add(randint(2, N))
    OP.append("%s %s" % (
        c,
        " ".join([str(x) for x in S])
    ))
    Q += 1

print(Q)
print("\n".join(OP))
