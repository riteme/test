#!/usr/bin/env pypy

from sys import argv
from random import *

n, m, q = map(int, argv[1:])
print m, q
for i in xrange(m + q):
    print randint(1, n), choice(["is-a", "has-a"]), randint(1, n)
