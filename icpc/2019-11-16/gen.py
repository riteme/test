#!/usr/bin/python

from sys import *
from random import *

T, n, m = map(int, argv[1:])

for t in xrange(T):
    print n, m
    for i in xrange(m):
        print randint(1, n), randint(1, n)
