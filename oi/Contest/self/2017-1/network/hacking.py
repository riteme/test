#!/usr/bin/env pypy

from os import system as sh

if sh("g++ implementer.cpp network.cpp -std=c++11 -g -o std.out"):
    exit(-1)
if sh("g++ implementer.cpp network-brute.cpp -std=c++11 -O3 -o brute.out"):
    exit(-1)

cnt = 1
while True:
    sh("./gen.py 5000 5000 > network.in")
    sh("./std.out > mine.out")
    sh("./brute.out > correct.out")

    if sh("diff -bB mine.out correct.out"):
        print("Hacked!")
        break
    else:
        print(cnt)
        cnt += 1
