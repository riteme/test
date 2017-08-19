#!/usr/bin/env pypy

from os import system as sh

sh("g++ main.cpp -O3 -std=c++11")
sh("g++ std.cpp -O3 -o std.out")

cnt = 1
while True:
    sh("./gen.py 10000 10000000000000 > soda.in")
    sh("./a.out < soda.in > soda.out")
    sh("./std.out < soda.in > soda.ans")

    if sh("diff -Bb soda.out soda.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
