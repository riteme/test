#!/usr/bin/python3

from os import *
from sys import *

def sh(x):
    assert not system(x)

sh('cp L-sa.cpp /tmp/a.cpp')
sh('cp L.cpp /tmp/b.cpp')
sh('cp gen.py /tmp/gen')
chdir('/tmp')
sh('g++ a.cpp -O3 -fsanitize=undefined -o a.out')
sh('g++ b.cpp -O3 -fsanitize=undefined -o b.out')
cnt = 0
while True:
    cnt += 1
    print(cnt)
    args = ' '.join(argv[1:])
    sh(f'./gen {args} > data.in')
    sh('./a.out < data.in > a.ans')
    sh('./b.out < data.in > b.ans')
