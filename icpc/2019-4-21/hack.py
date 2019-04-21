#!/usr/bin/pypy

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh("cp B.cpp /tmp")
sh("cp B-brute.cpp /tmp")
sh("cp gen.py /tmp")
chdir("/tmp")
sh("g++ B.cpp -std=c++14 -O3 -o a.out")
sh("g++ B-brute.cpp -O3 -o b.out")

cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py %s > data.in" % ' '.join(argv[1:]))
    sh("./a.out < data.in 2> a.err > a.tmp")
    sh("cat a.tmp | grep '\!' > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
