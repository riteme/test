#!/usr/bin/env pypy

from os import system as sh

sh("g++ forest.cpp -std=c++11 -o forest.exec")
sh("g++ forest-brute.cpp -O3 -o brute.exec")

cnt = 1
while True:
    sh("./gen.py 2 5 > forest.in")
    sh("./forest.exec < forest.in > forest.out")
    sh("./brute.exec < forest.in > forest.ans")

    if sh("diff -Bb forest.out forest.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
