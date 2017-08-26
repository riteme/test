#!/usr/bin/env pypy

from os import system as sh

sh("g++ mole.cpp -O3")
sh("g++ mole-brute.cpp -O3 -o brute.out")

cnt = 1
while True:
    sh("./mole-gen.py 3 1000000000 > mole.in")
    sh("./a.out < mole.in > mole.out")
    sh("./brute.out < mole.in > mole.ans")

    if sh("diff -Bb mole.out mole.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
