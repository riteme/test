#!/usr/bin/env pypy

from sys import *
from os import system as sh

a, b, n, q = argv[1:]
n, q = map(int, (n, q))

sh("g++ %s -std=c++11 -O3 -o /tmp/a.out" % a)
sh("g++ %s -std=c++11 -O3 -o /tmp/b.out" % b)

cnt = 1
while True:
    sh("./gen.py %s %s > /tmp/data.in" % (n, q))
    sh("/tmp/a.out < /tmp/data.in > /tmp/a.ans")
    sh("/tmp/b.out < /tmp/data.in > /tmp/b.ans")

    if sh("diff -Bb /tmp/a.ans /tmp/b.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
