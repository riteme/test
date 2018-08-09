#!/usr/bin/env pypy

from random import *
from sys import argv

T, n = map(int, argv[1:])
print T
for t in xrange(T):
    print n
    for i in xrange(2, n + 1):
        print i / 2, i
        # print randint(1, i - 1), i
