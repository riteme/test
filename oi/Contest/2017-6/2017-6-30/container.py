#!/usr/bin/env pypy

from sys import *
from random import *

n, K = map(int, argv[1:])

def random_seq():
    L = [0] * n
    for i in xrange(K):
        l = randint(0, n - 1)
        r = randint(l + 2, n + 1)
        print l, r

        for j in xrange(1, l + 1):
            L[j - 1] += 1
        for j in xrange(r, n + 1):
            L[j - 1] += 1

    return L

print " ".join(map(str, random_seq()))
