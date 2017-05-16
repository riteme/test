#!/usr/bin/env pypy

from os import system as sh

sh("g++ merchant.cpp -std=c++11 -O3 -o merchant.out")
sh("g++ merchant-brute.cpp -std=c++11 -O3 -o brute.out")

cnt = 1
while True:
    sh("./merchant-gen.py 100 1000 1000 1000000 > data.in")
    sh("./merchant.out < data.in > data.out")
    sh("./brute.out < data.in > data.ans")

    if sh("diff -Bb data.out data.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1;
