#!/usr/bin/env pypy

from os import system as sh

sh("g++ main.cpp -O3")
sh("g++ std.cpp -O3 -o std.out")

cnt = 1
while True:
    sh("./gen.py 5 10 9 > data.in")
    sh("./a.out < data.in > data.out")
    sh("./std.out < data.in > data.ans")

    if sh("diff -Bb data.out data.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
