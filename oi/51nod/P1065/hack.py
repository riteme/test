#!/usr/bin/env pypy

from os import system
def sh(x):
    return not system(x)

assert sh("g++ main-2.cpp -O3 -o a.out")
assert sh("g++ main.cpp -O3 -o b.out")

cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py 4 5 > data.in")
    assert sh("./a.out < data.in > a.ans")
    assert sh("./b.out < data.in > b.ans")
    assert sh("diff -Bb a.ans b.ans")
