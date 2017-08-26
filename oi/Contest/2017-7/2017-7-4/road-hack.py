#!/usr/bin/env pypy

from os import system as sh

sh("g++ road.cpp -O3")
sh("g++ road-brute.cpp -O3 -o brute.out")

cnt = 1
while True:
    sh("./road-gen.py 1000 5000 3000 1 > road.in")
    sh("./a.out < road.in > road.out")
    sh("./brute.out < road.in > road.ans")

    if sh("diff -Bb road.out road.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
