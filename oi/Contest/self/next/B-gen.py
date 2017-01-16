#!/usr/bin/env pypy

import sys
from random import *

def gen_graph():
    n = 30000
    m = 50000
    k = randint(1, n)
    E = set()

    while len(E) < m:
        u = randint(1, n - 1)
        v = randint(u + 1, n)

        E.add((u, v))

    L = ["%s %s" % x for x in E]

    print("%s %s %s" % (n, m, k))
    print("\n".join(L))

t = 18
print(t)

for i in range(0, t):
    gen_graph()
