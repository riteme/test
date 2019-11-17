#!/usr/bin/pypy

fib = [1, 1]
for n in xrange(2, 48):
    fib.append(fib[-1] + fib[-2])
for idx, v in enumerate(fib):
    print idx, v
