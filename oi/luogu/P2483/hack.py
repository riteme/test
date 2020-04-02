#!/usr/bin/python

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp main.cpp /tmp')
sh('cp std.cpp /tmp')
sh('cp gen.py /tmp')
chdir('/tmp')
sh('g++ main.cpp -O3 -o a.out')
sh('g++ std.cpp -O3 -o b.out')

cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen.py %s > data.in' % ' '.join(argv[1:]))
    sh('./a.out < data.in > a.ans 2> /dev/null')
    sh('./b.out < data.in > b.ans')
    sh('diff -Bb a.ans b.ans')