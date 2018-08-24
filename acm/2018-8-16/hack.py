#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh('cp G.cpp /tmp')
sh('cp G-std.cpp /tmp')
sh('cp G-gen.py /tmp')
chdir('/tmp')
sh('g++ G.cpp -O3')
sh('g++ G-std.cpp -O3 -o b.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./G-gen.py 10000 > data.in')
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')
