#!/usr/bin/env pypy

from sys import argv
from random import *

T, R = map(int, argv[1:])

print T
for i in xrange(T):
    l = randint(1, R)
    r = randint(l, R)
    v = randint(1, R)
    print l, r, v
