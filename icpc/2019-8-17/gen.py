#!/usr/bin/pypy

from sys import *
from random import *

n, CMAX = map(int, argv[1:])

print(n)
E = set()
while len(E) < n:
    E.add((randint(-CMAX, CMAX), randint(-CMAX, CMAX)))
print('\n'.join('%s %s' % x for x in E))
