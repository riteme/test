#!/usr/bin/pypy

import io
from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp F.cpp /tmp')
sh('cp F-std.cpp /tmp')
sh('cp F-gen.py /tmp')
chdir('/tmp')
sh('g++ F.cpp -std=c++11 -O3 -fsanitize=undefined')
sh('g++ F-std.cpp -std=c++11 -O3 -o b.out')
cnt = 0
while True:
    cnt += 1
    print cnt
    sh('./F-gen.py %s > data.in' % ' '.join(argv[1:]))
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
    with io.open('a.ans') as fp:
        mine = fp.read().strip()
    with io.open('b.ans') as fp:
        std = fp.read().strip()
    if mine == u'oo':
        assert std == u'oo', u'std = %s' % std
    elif std == u'oo':
        assert mine == u'oo', u'mine = %s' % mine
    else:
        mine = float(mine)
        std = float(std)
        delta = abs(std - mine)
        assert delta < 1e-6, 'mine = %.8f, std = %.8f, Δ = %.8f' % (mine, std, delta)
