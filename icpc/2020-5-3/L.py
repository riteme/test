#!/usr/bin/pypy

A, M, N = map(int, raw_input().split())

print '[1] A: %s' % A
for i in xrange(2, N + 1):
    d = max(map(int, str(A)))
    A = (A + d) % M
    print '%s: %s [+%s]' % (i, A, d)