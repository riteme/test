#!/usr/bin/env pypy

from os import system as sh

sh("g++ brute.cpp -O3 -o brute.exec")
sh("g++ main.cpp -g")

cnt = 1
while True:
    sh("./gen.py 100 100 2147483647 > data.in")
    sh("./a.out < data.in > data.out")
    sh("./brute.exec < data.in > data.ans")

    if sh("diff -Bb data.out data.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
