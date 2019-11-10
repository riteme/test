#!/usr/bin/pypy

T = int(raw_input())
for t in xrange(T):
    A, B, C = map(int, raw_input().split())
    D = A + B
    s = str(D / C) + '.'
    D %= C
    for i in xrange(50):
        D *= 10
        s += str(D / C)
        D %= C
    print s
