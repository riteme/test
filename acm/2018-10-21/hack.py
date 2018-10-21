#!/usr/bin/env pypy

from os import *

def sh(x):
    assert not system(x)

sh('cp 11.cpp /tmp')
sh('cp kstd.cpp /tmp')
sh('cp gen.py /tmp')
chdir('/tmp')
sh('g++ 11.cpp -O3 -o a.out')
sh('g++ kstd.cpp -O3 -o b.out')

cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen.py 42 2 > data.in')
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')
