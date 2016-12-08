#!/usr/bin/env pypy

from random import randint, choice, shuffle

N = 1000000

print(N)
for i in range(0, N):
    print("%s %s" % (randint(0, 1000), randint(0, 1000)))
