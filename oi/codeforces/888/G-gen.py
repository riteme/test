#!/usr/bin/python

from sys import *
from random import *

n, C = map(int, argv[1:])

print n
print ' '.join(str(randint(0, C)) for i in xrange(n))
