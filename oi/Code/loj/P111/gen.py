#!/usr/bin/pypy

from sys import *
from random import *

n, m = map(int, argv[1:])
s = ''.join(map(chr, xrange(ord('a'), ord('a') + m)))
print ''.join(choice(s) for i in xrange(n))
