#!/usr/bin/pypy

import io
from os import *
from sys import *
from random import *

def sh(x):
    assert not system(x)

sh('cp J.cpp /tmp')
sh('cp J-std.cpp /tmp')
sh('cp J-gen.py /tmp')
chdir('/tmp')
sh('g++ -std=c++14 J.cpp -O3')
sh('g++ -std=c++14 J-std.cpp -O3 -o b.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./J-gen.py %s > data.in' % ' '.join(argv[1:]))
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')
