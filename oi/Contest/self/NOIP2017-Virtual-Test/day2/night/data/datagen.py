#!/usr/bin/env pypy

from os import system as sh

def run(name, args, idx):
    l = idx[0]
    if len(idx) == 2:
        r = idx[1]
    else:
        r = idx[0]

    for i in range(l, r + 1):
        print "(info) Generating 'night%s.in'..." % i
        sh("./%s-gen.py %s > night%s.in" % (name, " ".join(map(str, args)), i))
        sh("./encoder < night%s.in > night%s.out" % (i, i))
        sh("mv night%s.out night%s.in" % (i, i))
        sh("./std < night%s.in > night%s.ans" % (i, i))

normal = "normal"  # n, q, K, RA, RB
random = "random"  # n, m, q
tree = "tree"      # n, q, d, extra
cactus = "cactus"  # n, q, d
friend = "friend"  # n, q, K, RA, RB

run(random, [10, 15, 1], [1])
run(normal, [100, 10, 6, 25, 10], [2])
run(normal, [1000, 10, 5, 2, 1], [3])
run(normal, [1000, 10, 13, 3, 1], [4])
run(normal, [100000, 10, 7, 2, 1], [5, 6])
run(normal, [100000, 10, 5, 3, 1], [7, 8])
run(normal, [100000, 100000, 13, 2, 1], [9])
run(normal, [100000, 100000, 97, 28, 10], [10, 11])
run(tree, [500000, 500000, 21, 0], [12])
run(tree, [500000, 500000, 31, 1], [13])
run(cactus, [500000, 500000, 17], [14, 15])
run(random, [500000, 1000000, 500000], [16, 17])
run(friend, [500000, 500000, 77, 2, 1], [18])
run(normal, [500000, 500000, 4079, 101, 100], [19])
run(normal, [500000, 500000, 103, 111, 100], [20])
run(normal, [500000, 500000, 23, 2, 1], [21, 22])
run(normal, [500000, 500000, 103, 2, 1], [23, 25])
