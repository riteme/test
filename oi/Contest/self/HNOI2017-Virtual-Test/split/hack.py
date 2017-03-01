#!/usr/bin/env pypy

from os import system as sh

if sh("g++ target.cpp -O3 -o target.exec"):
    exit(-1)
if sh("g++ std.cpp -O3 -o std.exec"):
    exit(-1)

cnt = 1
while True:
    sh("./gen.py 10 10 1000000000 100000 100000 > split.in")
    sh("./target.exec < split.in > split.out")
    sh("./std.exec < split.in > split.ans")

    if sh("diff -Bb split.out split.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
