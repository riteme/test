#!/usr/bin/env pypy

from os import system, chdir
from sys import *

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
    sh('./G-gen.py %s > data.in' % ' '.join(map(str, argv[1:])))
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    with open('a.ans', 'r') as reader:
        aAns = float(reader.readline())
    with open('b.ans', 'r') as reader:
        bAns = float(reader.readline())
    if abs(aAns - bAns) > 1e-6:
        print aAns, bAns, abs(aAns - bAns)
        exit(-1)

