#!/usr/bin/env pypy

from os import *
from sys import *

def sh(x):
    assert not system(x)

source = argv[1]
sh("cp {0} /tmp/{0}".format(source))
sh("cp gen.py /tmp/gen.py")
sh("cp chk.py /tmp/chk.py")
chdir('/tmp')
sh("g++ %s -std=c++11 -O3 -o a.out" % source)
cnt = 0
while True:
    cnt += 1
    print cnt
    sh("./gen.py 300000 1000000 > data.in")
    sh("./a.out < data.in > a.ans")
    sh("./chk.py a.ans")
