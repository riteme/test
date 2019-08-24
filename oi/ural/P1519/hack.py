#!/usr/bin/env pypy

from os import system as sh

sh("g++ main.cpp -std=c++11 -O3 -o mine.out")
sh("g++ std.cpp -O3 -o std.out")

cnt = 1
while True:
    sh("./gen.py 4 4 2 > data.in")
    sh("./mine.out < data.in > data.out")
    sh("./std.out < data.in > data.ans")

    if sh("diff -Bb data.out data.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
