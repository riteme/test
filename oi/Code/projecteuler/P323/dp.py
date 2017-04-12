#!/usr/bin/env python3

from math import *
import gmpy2
from gmpy2 import mpfr
gmpy2.get_context().precision = 2024

def c(n, m):
    return factorial(n) // factorial(m) // factorial(n - m)

f = [[0] * 33 for i in range(101)]
f[0][0] = 1
ans = mpfr(0))

for i in range(10):
    for j in range(33):
        for a in range(33):
            for b in range(max(0, a + j - 32), min(a, j) + 1):
                f[i + 1][a + j - b] += (f[i][a] *
                    c(a, b) * c(32 - a, j - b))
    assert sum(f[i + 1]) == 2**(32 * (i + 1))
    al = 2**(32 * (i + 1))
    tmp = (i + 1) * mpfr(f[i + 1][32]) / mpfr(al)
    #print(tmp)
    print (f[i+1])
    ans += tmp
print(ans)

