#!/usr/bin/env python3

from os import urandom
import gmpy2
from gmpy2 import mpfr, mpz
gmpy2.get_context().precision = 256

def randfloat(l, r, d):
    v = mpz(int.from_bytes(urandom(64), "little"))
    v %= (r - l) * 10**d
    return mpfr(v + l * 10**d) / 10**d

def readline():
    return [int(x) for x in input().split()]

n, q = readline()
bottom, top, left, right = readline()
P = []

for i in range(0, n):
    x, y, m = readline()
    P.append((mpfr(x), mpfr(y), mpfr(m)))

def force(M, m):
    L = (M[0] - m[0])**2 + (M[1] - m[1])**2
    return M[2] * m[2] / (L + gmpy2.sqrt(L))

def test(m):
    rx, ry = mpfr(0), mpfr(0)
    for M in P:
        dx = m[0] - M[0]
        dy = m[1] - M[1]
        
        if dx == 0 and dy == 0:
            continue

        dist = gmpy2.sqrt(dx**2 + dy**2)
        forc = force(M, m)
        rate = forc / dist
        rx += dx * rate
        ry += dy * rate

    return (rx, ry)

TIMES = 10**5

for i in range(0, q):
    weight, = readline()
    sumx, sumy = mpfr(0), mpfr(0)
    for j in range(0, TIMES):
        m = (
            mpfr(randfloat(left, right, 100)), 
            mpfr(randfloat(bottom, top, 100)),
            mpfr(weight)
        )
        ret = test(m)
        sumx += ret[0]
        sumy += ret[1]

    sumx /= TIMES
    sumy /= TIMES
    print(sumx, sumy)
