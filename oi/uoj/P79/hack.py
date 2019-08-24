#!/usr/bin/env pypy

from os import system as sh

cnt = 1
while True:
    sh("./gen.py 499 757 > data.in")
    if sh("./a.out < data.in > data.out"):
        print "Hacked!"
        break

    print cnt
    cnt += 1
