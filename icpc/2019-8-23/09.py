#!/usr/bin/python

from sys import *

def fac(n):
    return 1 if n < 2 else n * fac(n - 1)
def gcd(x, y):
    return x if y == 0 else gcd(y, x % y)

n, m = map(int, argv[1:])
num, dem = 0, 2**(n * m)
for k in xrange(1, min(n, m) + 1):
    lc = fac(n - 1) / fac(n - k)
    rc = fac(m - 1) / fac(m - k)
    num += (2 * k - 1) * lc * rc * 2**(n * m - k * k)
    print '%2s: %s' % (2 * k - 1, lc * rc * 2**(n * m - k * k))
r = gcd(num, dem)
print '%s/%s (%s/%s)' % (num/r, dem/r, num, dem)
