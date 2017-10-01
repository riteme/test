#!/usr/bin/env pypy

p = [0] * 20

p[0] = 1
for n in xrange(1, 20):
    for k in range(1, n + 1):
        for t in xrange(1, n / k + 1):
            p[n] += k * p[n - k * t]
    p[n] /= n

print ",".join(map(str, p))

q = [0] * 20

q[0] = 1
for n in xrange(1, 20):
    for k in range(1, n + 1, 2):
        for t in xrange(1, n / k + 1):
            q[n] += k * q[n - k * t]
    q[n] /= n

print ",".join(map(str, q))
