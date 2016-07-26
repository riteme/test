#!/usr/bin/env python3

from random import *

NMAX = 200000
MMAX = 20000
AMAX = 1000000000


def random_interval(left, right):
    u = randint(left, right)
    v = randint(u, right)
    return (u, v)

print("%s %s" % (NMAX, MMAX))
print("\n".join(
    ["%s %s" % random_interval(1, AMAX) for i in range(0, NMAX)]
))
