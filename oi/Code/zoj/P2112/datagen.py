#!/usr/bin/env pypy

from random import randint, choice, shuffle

CMAX = 10
N = 10
Q = 20

print(1)
print("%s %s" % (N, Q))

L = [str(randint(1, CMAX)) for i in range(0, N)]
print(" ".join(L))

for i in range(0, Q):
    t = randint(1, 2)

    if t == 1:
        print("C %s %s" % (randint(1, N), randint(1, CMAX)))
    elif t == 2:
        i = randint(1, N)
        j = randint(i, N)
        print("Q %s %s %s" % (i, j, randint(1, j - i + 1)))
