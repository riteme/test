#!/usr/bin/env pypy

from sys import argv
from random import *

n, = map(int, argv[1:])

S = ['('] * n + [')'] * n
shuffle(S)
print "".join(S)
