#!/usr/bin/env pypy

from os import system as sh

sh("g++ love.cpp -O3")
sh("g++ love-brute.cpp -O3 -o brute.out")

cnt = 1
while True:
    sh("./love-gen.py 10 1000000 > love.in")
    sh("./a.out < love.in > love.out")
    sh("./brute.out < love.in > love.ans")

    if sh("diff -Bb love.out love.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
