#!/usr/bin/python2

from random import *

n = 5
CMAX = 9

for i in xrange(10000):
    print n
    print ' '.join(str(randint(-CMAX, CMAX)) for i in xrange(n))
    print ' '.join(str(randint(-CMAX, CMAX)) for i in xrange(n))