#!/usr/bin/env python3

from random import *

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

def quick_pow(_a, _b, m):
    r, a, b = 1, _a, _b

    while b:
        if b & 1:
            r = r * a % m
        a = a * a % m
        b >>= 1

    return r

def miller_rabin(n):
    BASIS = [2, 7, 61, 353, 735283, 71]

    t = n - 1
    k = 0
    while not (t & 1):
        k += 1
        t >>= 1

    for b in BASIS:
        if n == b:
            continue

        v = quick_pow(b % n, t, n)

        for i in range(0, k):
            u = v**2 % n

            if u == 1 and v != 1 and v != n - 1:
                return False

            v = u

        if v != 1:
            return False

    return True


def pollard_rho(n, a):
    i, k = 1, 2
    x = randrange(0, n)
    y = x
    while True:
        x = (x**2 + a) % n
        i += 1

        if y == x:
            return 0

        r = gcd(y - x, n)
        if r != 1 and r != n:
            return r

        if k == i:
            k <<= 1
            y = x

def _factor(n):
    if miller_rabin(n):
        return [n]

    d = 0
    a = 140
    while a > 0 and d == 0:
        d = pollard_rho(n, a)
        a -= 1

    assert d > 1, "Pollard rho failed."

    return _factor(d) + _factor(n // d)

def factor(n):
    return sorted(_factor(n))

if __name__ == "__main__":
    try:
        n = int(input())

        print("{}: {}".format(n, " ".join([str(x) for x in factor(n)])))
    except EOFError:
        pass
