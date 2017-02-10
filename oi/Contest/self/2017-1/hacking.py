#!/usr/bin/env pypy

import sys
from os import system as sh

if len(sys.argv) < 2:
    print("Usage: %s [NAME]" % sys.argv[0])
    exit(-1)

name = sys.argv[1]
if sh("g++ -std=c++11 {0}.cpp -o {0}.exec".format(name)):
    exit(-1)
if sh("g++ -std=c++11 {0}-brute.cpp -O3 -o {0}-brute.exec".format(name)):
    exit(-1)

cnt = 1
while True:
    sh("./{0}-gen.py > {0}.in".format(name))
    sh("./{0}.exec < {0}.in > {0}.out".format(name))
    sh("./{0}-brute.exec < {0}.in > {0}.ans".format(name))

    if sh("diff -Bb {0}.out {0}.ans".format(name)):
        print("Hacked!")
        break
    else:
        print(cnt)
        cnt += 1
