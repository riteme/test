#!/usr/bin/pypy

from random import *

print 100
for i in xrange(100):
    print 250, 250
    print '\n'.join(
        ''.join(choice("0" * 150 + "1") for j in xrange(250))
        for k in xrange(250)
    )
