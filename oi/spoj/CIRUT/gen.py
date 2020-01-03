#!/usr/bin/python

from sys import *
from random import *

n, R, C = map(int, argv[1:])

print n
P = set()
while len(P) < n:
    x = randint(1, C)
    y = randint(1, C)
    r = randint(1, R)
    P.add((x, y, r))

for x, y, r in P:
    print x, y, r
