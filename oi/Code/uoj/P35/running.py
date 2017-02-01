#!/usr/bin/env pypy

from os import system as sh

cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py > data.in")
    if sh("./a.out < data.in > /dev/null"):
        print "RE"
        break
