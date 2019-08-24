#!/usr/bin/env pypy

from os import *
from sys import *
from shutil import *
sh = system

copy("gen.py", "/tmp/gen.py")
copy("SAIS-2.cpp", "/tmp/code.cpp")
copy("SAIS.cpp", "/tmp/std.cpp")
chdir("/tmp")
sh("g++ code.cpp -O3 -o a.out")
sh("g++ std.cpp -O3 -o b.out")

cnt = 1
while True:
    sh("./gen.py %s > data.in" % " ".join(map(str, argv[1:])))
    sh("./a.out < data.in > a.ans")
    sh("./b.out < data.in > b.ans")

    if sh("diff -Bb a.ans b.ans"):
        print "Hacked!"
        break

    print cnt
    cnt += 1
