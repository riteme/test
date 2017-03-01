#!/usr/bin/env pypy

from os import system as sh

if sh("g++ brute.cpp -std=c++11 -O3 -o brute.exec"):
    exit(-1)
if sh("g++ std.cpp -std=c++11 -g -o std.exec"):
    exit(-1)

cnt = 1
while True:
    sh("./gen.py 1000 5000 0 > bipartite.in")
    sh("./std.exec < bipartite.in > bipartite.out")
    sh("./brute.exec < bipartite.in > bipartite.ans")

    if sh("diff -Bb bipartite.out bipartite.ans"):
        print "Hacked!"
        break
    else:
        print cnt
        cnt += 1

