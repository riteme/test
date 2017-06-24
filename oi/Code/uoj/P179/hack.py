#!/usr/bin/env pypy

from os import system as sh

sh("g++ simplex.cpp -O3 -o simplex.out")
sh("g++ std.cpp -O3 -o std.out")

cnt = 1
while True:
    sh("./gen.py 20 20 > data.in")
    sh("./simplex.out < data.in > data.out")
    sh("./std.out < data.in > data.ans")

    with open("data.ans", "r") as reader:
        std = reader.readline().strip()
    with open("data.out", "r") as reader:
        usr = reader.readline().strip()

    if std == "Infeasible" or std == "Unbounded":
        if usr != std:
            print "Hacked!"
            break
    elif abs(float(std) - float(usr)) >= 1e-4:
        print "Hacked!"
        break

    print cnt
    cnt += 1
