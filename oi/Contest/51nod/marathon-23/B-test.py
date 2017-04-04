#!/usr/bin/env python3

from random import *

def test(n, P):
    S = 0
    while True:
        v = randrange(0, n)

        S += v
        if v in P:
            return S

n = int(input())
P = [int(x) for x in input().split()]
T = 10**6
S = [test(n, P) for i in range(T)]
print(sum(S) / T)
