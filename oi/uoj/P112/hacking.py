#!/usr/bin/env pypy

from os import system as sh

if sh("g++ brute1.cpp -std=c++11 -O3 -o brute.exec"):
    exit(-1)
if sh("g++ palembang-bridges.cpp -std=c++11 -g -o mine.exec"):
    exit(-1)

cnt = 1
while True:
    sh("./gen.py 100 1000000000 > data.in")
    sh("./brute.exec < data.in > data.ans")
    sh("./mine.exec < data.in > data.out")

    if sh("diff -Bb data.out data.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
