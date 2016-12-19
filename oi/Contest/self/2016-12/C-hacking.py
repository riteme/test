#!/usr/bin/env pypy

from os import system as sh

sh("g++ C.cpp -std=c++11 -o C.out")
sh("g++ C-brute.cpp -std=c++11 -O3 -o C-brute.out")

cnt = 1
while True:
    sh("./C-gen.py > C.in")
    sh("./C.out < C.in > mine.out")
    sh("./C-brute.out < C.in > brute.out")

    if sh("diff -bB mine.out brute.out"):
        print("Hacked!")
        break
    else:
        print(cnt)
        cnt += 1
