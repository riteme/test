#!/usr/bin/env pypy

from random import randint, choice, shuffle

L = 10000
N = 1000000

print("%s %s" % (N, L))

for i in range(1, N + 1):
    print("%s %s" % (randint(1, L), randint(1, L)))
