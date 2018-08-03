#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh("cp J-spfa.cpp /tmp")
sh("cp J-std.cpp /tmp")
sh("cp J-gen.py /tmp")
chdir("/tmp")
sh("g++ J-spfa.cpp -O3 -o a.out")
sh("g++ J-std.cpp -O3 -o b.out")
cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./J-gen.py 5 9 9 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
