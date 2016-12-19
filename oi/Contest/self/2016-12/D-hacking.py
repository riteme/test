#!/usr/bin/env pypy

from os import system as sh

sh("g++ D.cpp -std=c++11 -o D-mine")
sh("g++ D-brute.cpp -std=c++11 -O3 -o D-brute")

cnt = 1
while True:
    sh("./D-gen.py > D.in")
    sh("./D-mine < D.in > mine.out")
    sh("./D-brute < D.in > brute.out")

    if sh("diff -bB mine.out brute.out"):
        print("Hacked!")
        break
    else:
        print(cnt)
        cnt += 1
