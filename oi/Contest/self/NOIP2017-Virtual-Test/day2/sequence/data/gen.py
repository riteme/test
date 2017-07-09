#!/usr/bin/env pypy

from random import *
from sys import *

n, allzero = map(int, argv[1:])

if allzero:
    print '.' * n
else:
    print "".join([choice(['.'] * 5 + ['1', '0']) for i in xrange(n)])
