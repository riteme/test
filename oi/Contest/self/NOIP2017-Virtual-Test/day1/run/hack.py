#!/usr/bin/env pypy

from os import system as sh

sh("clang++ travel.cpp -std=c++11 -O3")
sh("clang++ travel-brute.cpp -std=c++11 -O3 -o brute.out")

cnt = 1
while True:
    sh("./gen.py 20 7 100> travel.in")
    sh("./a.out < travel.in > travel.out")
    sh("./brute.out < travel.in > travel.ans")

    if sh("diff -Bb travel.out travel.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
