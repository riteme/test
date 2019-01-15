#!/usr/bin/env pypy

from sys import argv

EPS = 1e-2
with open(argv[1], "r") as reader:
    a = float(reader.readline())
with open(argv[2], "r") as reader:
    b = float(reader.readline())
if abs(a - b) >= EPS:
    print a
    print b
    print "diff: %.10f" % abs(a - b)
    exit(-1)
