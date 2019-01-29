#!/usr/bin/env pypy

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp C-dp.cpp /tmp/dp.cpp')
sh('cp C.cpp /tmp/a.cpp')
sh('cp C-gen.py /tmp')
sh('cp max.cpp /tmp')
chdir('/tmp')
sh('g++ dp.cpp -O3 -o b.out')
sh('g++ a.cpp -O3 -o a.out')
sh('g++ max.cpp -O3 -o max.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./C-gen.py %s > _data.in' % argv[1])
    sh('./max.out < _data.in > data.in')
    sh('tail -n +2 _data.in >> data.in')
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')
