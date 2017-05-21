#!/usr/bin/env pypy

from os import system as sh

sh("g++ bracket.cpp -g")

cnt = 1
while True:
    sh("./bracket-gen.py 6 > data.in")
    if sh("./a.out < data.in > /dev/null"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
