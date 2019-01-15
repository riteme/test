#!/usr/bin/env pypy

t, n = map(int, raw_input().split())
[raw_input() for i in xrange(n - 1)]
verdict = raw_input().strip()
if verdict == 'Random':
    exit(-1)
