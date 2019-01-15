#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh("cp J.cpp /tmp")
sh("cp J-brute.cpp /tmp")
sh("cp gen.py /tmp")
chdir("/tmp")
sh("g++ -std=c++11 -DNDEBUG J.cpp -O3 -o a.out")
sh("g++ J-brute.cpp -O3 -o b.out")

cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py 5 5000 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
