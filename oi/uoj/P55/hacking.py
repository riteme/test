#!/usr/bin/env pypy

from os import system as sh

if sh("g++ flower.cpp -std=c++11 -o flower.exec"):
    exit(-1)
if sh("g++ flower-brute.cpp -std=c++11 -O3 -o brute.exec"):
    exit(-1)

cnt = 1
while True:
    sh("./gen.py 200 > flower.in")
    sh("./flower.exec < flower.in > flower.out")
    sh("./brute.exec < flower.in > flower.ans")

    if sh("diff -Bb flower.out flower.ans"):
        print("Hacked!")
        break
    else:
        print(cnt)
        cnt += 1
