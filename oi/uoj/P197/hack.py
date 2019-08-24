#!/usr/bin/pypy

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp std.cpp /tmp')
sh('cp brute.cpp /tmp')
sh('cp circuit.cpp /tmp')
sh('cp gen.py /tmp')
chdir('/tmp')
sh('clang++ circuit.cpp -O3 -D NDEBUG -o a.out')
sh('clang++ std.cpp -O3 -o b.out')
#sh('clang++ brute.cpp -O3 -o b.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen.py %s > data.in' % ' '.join(map(str, argv[1:])))
    sh('./a.out < data.in > a.ans 2> stderr.out')
    sh('./b.out < data.in > b.ans 2> stderr.out')
    sh('diff -Bb a.ans b.ans')
