#!/usr/bin/env python3

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('g++ main.cpp -fsanitize=undefined -g')
sh('g++ std.cpp -O3 -o b.out')

cnt = 0
while True:
    cnt += 1
    print(cnt)
    sh('./gen.py %s %s > data.in' % tuple(argv[1:]))
    sh('./a.out < data.in > data.out')
    sh('./b.out < data.in > data.ans')
    sh('diff -Bb data.{out,ans}')
