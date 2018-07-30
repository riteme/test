#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh("cp E.cpp /tmp")
sh("cp E-std.cpp /tmp")
sh("cp E-gen.py /tmp")
chdir("/tmp")
sh("g++ E.cpp -std=c++11 -O3 -o a.out")
sh("g++ E-std.cpp -O3 -o b.out")
cnt = 0;
while True:
    cnt += 1
    print cnt
    sh("./E-gen.py 4 6 10 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")