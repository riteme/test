#!/usr/bin/env pypy

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp nm.cpp /tmp')
sh('cp std.cpp /tmp')
sh('cp gen.py /tmp')
chdir('/tmp')
sh('g++ nm.cpp -O3')
sh('g++ std.cpp -O3 -o b.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen.py %s > data.in' % ' '.join(argv[1:]))
    sh('./a.out < data.in > a.ans 2> stderr.log')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')
