#!/usr/bin/env pypy

from sys import argv

n = int(argv[1])

marked = [False] * (n + 10)
primes = []
marked[0] = True
marked[1] = True
for i in xrange(2, n + 10):
    if not marked[i]:
        primes.append(i)
    for p in primes:
        if i * p <= n:
            marked[i * p] = True
        else:
            break
        if i % p == 0:
            break

print "Searched", len(primes), "primes."

mask = [True] * (n + 1)

for i in xrange(1, n + 1):
    for j in xrange(1, n / i + 1):
        if marked[i + j]:
            mask[i * j] = False

print "Processed all numbers."

s = 0
for i in xrange(1, n + 1):
    if mask[i]:
        print i
        s += 1

print s
