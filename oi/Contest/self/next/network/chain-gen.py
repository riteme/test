#!/usr/bin/env pypy

from random import *

N = 100000

print("%s %s" % (N, N))
for i in range(2, 15001):
    print("%s %s %s" % (i - 1, i, N))
for i in range(15001, 30001):
    print("%s %s %s" % (i, i - 1, N))
for i in range(0, 30001):
    print("%s %s %s" % (23333, 29999, N))
for i in range(0, 40000):
    print("%s %s %s" % (1, 1, N))
