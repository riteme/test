#!/usr/bin/env pypy

a, n = map(int, raw_input().split())
dp = [0] * (n + 1)
for i in xrange(1, n + 1):
    k = 1
    while k <= i:
        dp[i] |= dp[i - k] ^ 1
        k *= a
print ''.join(map(str, dp))
