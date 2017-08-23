#!/usr/bin/env pypy

from sys import *
from os import system as sh

a, b, n, q = argv[1:]
n, q = map(int, (n, q))

sh("g++ %s -std=c++11 -O3 -o a.out" % a)
sh("g++ %s -std=c++11 -O3 -o b.out" % b)

cnt = 1
while True:
    sh("./gen.py %s %s > data.in" % (n, q))
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")

    if sh("diff -Bb a.ans b.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
