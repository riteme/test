#!/usr/bin/python

from sys import *
from random import *

n = int(argv[1])
P = range(1, n + 1)
shuffle(P)
print n
print ' '.join(map(str, P))
