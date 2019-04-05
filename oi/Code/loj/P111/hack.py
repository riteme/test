#!/usr/bin/pypy

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp SAIS.cpp /tmp')
sh('cp DC3.cpp /tmp')
sh('cp gen.py /tmp')
chdir("/tmp")
sh("g++ SAIS.cpp -O3 -o a.out")
sh("g++ DC3.cpp -O3 -o b.out")

cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py %s > data.in" % ' '.join(argv[1:]))
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
