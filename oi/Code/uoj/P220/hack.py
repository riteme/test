#!/usr/bin/env pypy

from os import system as sh

sh("g++ brute.cpp -std=c++11 -O3 -o brute.out")
sh("g++ grid.cpp -std=c++11 -O3")

cnt = 1
while True:
    sh("./gen.py 6 6 > data.in")
    sh("./brute.out < data.in > data.ans")
    sh("./a.out < data.in > data.out")

    if sh("diff -Bb data.out data.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
