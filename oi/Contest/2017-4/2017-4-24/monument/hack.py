#!/usr/bin/env pypy

from os import system as sh

if sh("g++ monument.cpp -O3 -o monument.exec"):
    exit(-1)
if sh("g++ brute.cpp -O3 -o brute.exec"):
    exit(-1)

cnt = 1
while True:
    sh("./gen.py 500 1000000000 > monument.in")
    sh("./monument.exec < monument.in > monument.out")
    sh("./brute.exec < monument.in > monument.ans")

    if sh("diff -Bb monument.out monument.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
