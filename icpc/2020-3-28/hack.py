#!/usr/bin/python2

from os import *

def sh(x):
    assert not system(x)

sh('cp E.cpp /tmp')
sh('cp E-std2.cpp /tmp')
sh('cp E-gen.py /tmp/gen')
chdir('/tmp')
sh('g++ E.cpp -O2 -fsanitize=undefined')
sh('g++ E-std2.cpp -O2 -o b.out')

cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen > data.in')
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')