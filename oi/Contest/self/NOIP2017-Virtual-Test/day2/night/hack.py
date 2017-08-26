#!/usr/bin/env pypy

from os import system as sh
from sys import *

a, b = argv[1:]

sh("g++ %s -O3 -std=c++11 -o a.out" % a)
sh("g++ %s -O3 -std=c++11 -o b.out" % b)

cnt = 1
while True:
    sh("./random-gen.py 500 550 500 > night.in")
    sh("./a.out < night.in > night.out")
    sh("./b.out < night.in > night.ans")

    if sh("diff -Bb night.out night.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
