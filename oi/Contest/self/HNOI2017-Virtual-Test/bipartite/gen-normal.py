#!/usr/bin/env pypy

import sys
from random import *

if len(sys.argv) < 4:
    print "Usage: %s [N] [Q] [S]" % sys.argv[0]
    exit(-1)

n = int(sys.argv[1])
q = int(sys.argv[2])
s = int(sys.argv[3])

assert q >= n * 5, "q is too small"

def random_partition(n):
    S1 = set(sample(range(1, n + 1), n / 2))
    S2 = set(range(1, n + 1)) - S1
    return S1, S2

def random_bipartite(n, m):
    S1, S2 = random_partition(n)
    S1, S2 = list(S1), list(S2)
    E = set()
    while len(E) < m:
        u, v = choice(S1), choice(S2)
        E.add((u, v))

    return E

E1 = random_bipartite(n, min(n**2 / 4, n + n / 4))
E2 = random_bipartite(n, min(n**2 / 4, n + n / 4))
ER = E1 ^ E2
E1 = list(E1)
E2 = list(E2)
shuffle(E1)
shuffle(E2)

print n, q, s

pos = 1
A = set()
Q = []

def random_operation(c):
    global A
    global n
    global pos
    OP = ["ADD", "DEL", "DEL"]

    while c:
        op = choice(OP)

        if op == "ADD":
            u, v = randint(1, n), randint(1, n)
            A.add(pos)
            Q.append("ADD %s %s" % (u, v))
        else:
            if len(A) == 0:
                continue

            u = A.pop()
            Q.append("DEL %s" % u)

        pos += 1
        c -= 1

for idx, (u, v) in enumerate(E1, 1):
    A.add(idx)
    pos += 1
    Q.append("ADD %s %s" % (u, v))

lbound = pos
A.add(pos)
Q.append("ADD %s %s" % (1, 1))
pos += 1
random_operation(n / 2 - 1)
rbound = pos

need_remove = []
for idx in A:
    if lbound <= idx and idx < rbound:
        need_remove.append(idx)
        Q.append("DEL %s" % idx)

pos += len(need_remove)
for idx in need_remove:
    A.remove(idx)

for idx, (u, v) in enumerate(E1, 1):
    if (u, v) in ER and idx in A:
        A.remove(idx)
        pos += 1
        Q.append("DEL %s" % idx)

for idx, (u, v) in enumerate(E2, pos):
    A.add(idx)
    Q.append("ADD %s %s" % (u, v))

pos += len(E2)

if pos <= q:
    random_operation(q - pos + 1)

print "\n".join(Q[:q])
