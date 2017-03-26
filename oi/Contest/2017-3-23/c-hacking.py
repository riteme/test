#!/usr/bin/env pypy

from os import system as sh

if sh("g++ c-brute.cpp -O3 -o brute.exec"):
    exit(-1)
if sh("g++ c.cpp -O3 -o c.exec"):
    exit(-1)

cnt = 1
while True:
    sh("./c-gen.py 1000 100 1000000000 > c.in")
    sh("./c.exec < c.in > c.out")
    sh("./brute.exec < c.in > c.ans")

    if sh("diff -Bb c.out c.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
