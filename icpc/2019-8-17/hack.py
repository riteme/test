#!/usr/bin/pypy

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp G.cpp /tmp')
sh('cp b.out /tmp')
sh('cp gen.py /tmp')
chdir('/tmp')
sh('g++ G.cpp -g -fsanitize=undefined -DNDEBUG')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./gen.py %s > data.in' % ' '.join(argv[1:]))
    with popen('./a.out < data.in') as r:
        out = float(r.read())
    with popen('./b.out < data.in') as r:
        ans = float(r.read())
    assert abs(out - ans) < 1e-7, ('Δ = %.9lf' % abs(out - ans))

