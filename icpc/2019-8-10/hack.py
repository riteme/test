#!/usr/bin/pypy

from os import system, chdir

def sh(x):
    assert not system(x)

sh('cp H.cpp /tmp')
sh('cp b.out /tmp')
sh('cp H-gen.py /tmp/gen.py')
chdir('/tmp')
sh('g++ H.cpp -O3 -o a.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen.py 2500 4 5000 10 26 > data.in')
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')
