#!/usr/bin/env pypy

from os import *
sh = system

sh("g++ main.cpp -O3 -o /tmp/a.out")
sh("g++ brute.cpp -O3 -o /tmp/b.out")
sh("cp gen.py /tmp/gen.py")
chdir("/tmp")

cnt = 1
while True:
    print cnt
    cnt += 1

    sh("./gen.py 1000 1000000000 1000000 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")

    if sh("diff -Bb a.ans b.ans"):
        print "Hacked!"
        break
