#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh("cp I.cpp /tmp")
sh("cp I-std.cpp /tmp")
sh("cp I-gen.py /tmp")
chdir("/tmp")
sh("g++ I.cpp -std=c++11 -O3")
sh("g++ I-std.cpp -std=c++11 -O3 -o b.out")
cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./I-gen.py 100000 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
