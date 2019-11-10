#!/usr/bin/pypy

T = int(raw_input())
for t in xrange(T):
    n = int(raw_input())
    m = n % 4
    n = n / 4 * 4
    ans = 0
    for i in xrange(0, m + 1):
        ans ^= n + i
    print ans
