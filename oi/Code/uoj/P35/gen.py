#!/usr/bin/env pypy

from random import *

N = 100000

print "".join([choice(['a', 'b']) for i in range(0, N)])
