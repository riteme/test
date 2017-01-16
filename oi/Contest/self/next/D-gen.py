#!/usr/bin/env pypy

from random import *

NMAX = 5 * 10**6
KMAX = 10**4
MMAX = 10**3
# NMAX = 10
# KMAX = 5
# MMAX = 10

cnt = 0
Q = []
def gen_tree(left, right, father = 0):
    global KMAX
    global cnt
    global Q

    if right < left:
        return

    mid = (left + right) // 2

    cnt += 1
    me = cnt
    if father:
        print("%s %s" % (father, me))

    gen_tree(left, mid - 1, me)
    gen_tree(mid + 1, right, me)

    if cnt == me and len(Q) < KMAX:
        Q.append(str(me))
# def gen_tree(n):
#     for i in range(2, n + 1):
#         u = randrange(max(1, i - 10), i)
#         print("%s %s" % (u, i))

print("%s %s" % (NMAX, MMAX))
gen_tree(1, NMAX)
for i in range(0, MMAX):
    Q = [str(randint(1, NMAX)) for i in range(KMAX)]
    print("%s %s" % (len(Q), " ".join(Q)))
