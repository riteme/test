#!/usr/bin/env pypy

from os import *
sh = system

sh("g++ earthworm.cpp -O3 -o a.out")
sh("g++ target.cpp -O3 -o b.out")

cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py 3 2 5 2 2 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")

    if sh("diff -Bb a.ans b.ans"):
        print "Hacked!"
        break
