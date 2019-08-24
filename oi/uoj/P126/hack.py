#!/usr/bin/env pypy

from os import system as sh

if sh("g++ main.cpp -std=c++11 -O3 -o main.exec"):
    exit(-1)
if sh("g++ center.cpp -std=c++11 -O3 -o brute.exec"):
    exit(-1)

cnt = 1
while True:
    sh("./gen.py 7 10 > data.in")
    sh("./main.exec < data.in > data.out")
    sh("./brute.exec < data.in > data.ans")

    if sh("diff -Bb data.out data.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
