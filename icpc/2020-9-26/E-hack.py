from os import *

def sh(x):
    assert not system(x)

sh('g++ E.cpp -O0 -g -fsanitize=undefined')
cnt = 0
while True:
    cnt += 1
    print(cnt)
    sh('python E-gen.py > E.in')
    sh('./a.out < E.in > E.out')
    sh('./std.out < E.in > E.ans')
    sh('diff -Bb E.{out,ans}')
