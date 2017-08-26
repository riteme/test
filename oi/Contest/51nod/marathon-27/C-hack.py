#!/usr/bin/env pypy

from os import system as sh

sh("g++ C.cpp -O3")
sh("g++ C-brute.cpp -O3 -o b.out")

cnt = 1
while True:
    sh("./C-gen.py 10 30 2 > C.in")
    sh("./a.out < C.in > C.out")
    sh("./b.out < C.in > C.ans")

    if sh("diff -Bb C.out C.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
