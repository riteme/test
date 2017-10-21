#!/usr/bin/env pypy

from os import *
from shutil import *
sh = system

sh("g++ main.cpp -O3 -std=c++11")
sh("g++ main-2.cpp -O3 -o b.out")

cnt = 1
while True:
    print cnt
    sh("./gen.py 5 10 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")

    if sh("diff -Bb a.ans b.ans"):
        print "Hacked!"
        break

    cnt += 1
