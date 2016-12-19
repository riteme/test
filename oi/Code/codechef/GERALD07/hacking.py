#!/usr/bin/env python3

from os import system as sh

cnt = 1
while True:
    sh("./graph-gen.py > graph.in")
    sh("./a.out < graph.in > graph.out")
    sh("./brute.out < graph.in > std.out")

    if sh("diff -bB graph.out std.out"):
        print("Hacked!")
        break
    else:
        print(cnt)
        cnt += 1
