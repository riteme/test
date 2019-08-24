#!/usr/bin/env pypy

from sys import *
from random import *

n, SIGMA = map(int, argv[1:])
SIGMA = [chr(x) for x in xrange(ord('a'), ord('a') + SIGMA)]
print "".join([choice(SIGMA) for i in xrange(n)])
