#!/usr/bin/env pypy

from sys import *
from random import *

n, m = map(int, argv[1:])
print n
print ' '.join(map(str, (randint(-m, m) for i in xrange(n))))
