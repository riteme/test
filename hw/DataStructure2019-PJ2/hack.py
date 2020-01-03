#!/usr/bin/env python

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp main.cpp /tmp')
sh('cp brute.cpp /tmp')
sh('cp random-gen.py /tmp/gen')
chdir('/tmp')
sh('g++ -std=c++17 -DNDEBUG main.cpp -fsanitize=undefined -o a.out')
sh('g++ brute.cpp -o b.out -O3')

cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen %s > data' % (' '.join(argv[1:])))
    sh('./a.out < data > a.ans 2> /dev/null')
    sh('./b.out < data > b.ans 2> /dev/null')
    sh('diff a.ans b.ans')