#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh('cp C.cpp /tmp')
sh('cp C-std.cpp /tmp')
sh('cp C-gen.py /tmp')
chdir('/tmp')
sh('g++ C.cpp -O3')
sh('g++ C-std.cpp -O3 -o b.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./C-gen.py 150000 200000 > data.in')
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')
