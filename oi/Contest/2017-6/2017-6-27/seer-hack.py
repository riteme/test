#!/usr/bin/env pypy

from os import system as sh

sh("g++ seer.cpp -O3")

cnt = 1
while True:
    sh("./seer-gen.py 100000 250000 1000 > seer.in")
    sh("./a.out < seer.in > seer.out")

    with open("seer.out", "r") as reader:
        ans = int(reader.readline())

    if ans == -1:
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1
