#!/usr/bin/env pypy

from os import system, chdir

def sh(x):
    assert not system(x)

sh("cp * /tmp")
chdir("/tmp")

sh("g++ main.cpp -g -std=c++11 -DNDEBUG -o a.out")
sh("g++ b.cpp -O3 -o b.out")
cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py 5 5 3 20 100 10 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")
    sh("diff -Bb a.ans b.ans")
