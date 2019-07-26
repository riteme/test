#!/usr/bin/pypy

from os import *

def sh(x):
    assert not system(x)

sh("cp C-std.cpp /tmp")
sh("cp C-nlog2n.cpp /tmp")
sh("cp gen.py /tmp")
chdir("/tmp")
sh("g++ C-std.cpp -std=c++11 -O3 -o b.out")
sh("g++ C-nlog2n.cpp -O3 -o a.out")
cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py 10000 10 10 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
