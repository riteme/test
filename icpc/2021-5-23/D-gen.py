#!/usr/bin/env python3

from random import *

c = 200000
n, q = c, c
C = 10**8

print(n, q)
for i in range(n):
    l = randint(0, C - 1)
    r = randint(l + 1, C)
    print(l, r)
for i in range(q):
    l = randint(1, n)
    r = randint(l, n)
    print(l, r)
