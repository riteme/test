#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh("cp B.cpp /tmp")
sh("cp B-std.cpp /tmp")
sh("cp B-gen.py /tmp")
sh("cp B-chk.py /tmp")
chdir("/tmp")
sh("g++ B.cpp -std=c++11 -O3 -o a.out")
sh("g++ B-std.cpp -O3 -o b.out")
cnt = 0;
while True:
    cnt += 1
    print cnt
    sh("./B-gen.py 100 10000 10000 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("./B-chk.py a.ans b.ans")
