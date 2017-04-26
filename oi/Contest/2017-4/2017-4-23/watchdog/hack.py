#!/usr/bin/env pypy

from os import system as sh

sh("g++ watchdog.cpp -O3 -o mine.exec")
sh("g++ owen.cpp -O3 -o owen.exec")

cnt = 1
while True:
    sh("./gen.py 8000 1000000000 > watchdog.in")
    sh("./mine.exec")
    sh("./owen.exec > watchdog.ans")

    if sh("diff -Bb watchdog.out watchdog.ans"):
        print "FUCK"
        break
    else:
        print cnt
        cnt += 1
