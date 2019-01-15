#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh("cp A.cpp /tmp")
sh("cp A-std.cpp /tmp")
sh("cp A-gen.py /tmp")
chdir("/tmp")
sh("g++ A.cpp -O3")
sh("g++ A-std.cpp -O3 -o b.out")
cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./A-gen.py 5000 1000000 200 > data.in")
    #sh("./A-gen.py 10 40 3 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
