#!/usr/bin/env pypy

from os import system

def sh(x):
    assert not system(x)

sh("g++ main.cpp -g -o a.out")
sh("g++ std.cpp -O3 -o b.out")

cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py 100 5000 100000 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
