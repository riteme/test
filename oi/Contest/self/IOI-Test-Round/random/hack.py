#!/usr/bin/env pypy

from os import system as sh

sh("g++ random.cpp -O3 -o random.out")
sh("g++ brute.cpp -O3 -o brute.out")

for i in xrange(1, 10**9):
    sh("./random-gen.py 40 600 1000000007 > data.in")
    sh("./random.out < data.in > data.out")
    sh("./brute.out < data.in > data.ans")

    if sh("diff -Bb data.out data.ans"):
        print "Hacked!"
        break
    else:
        print i
