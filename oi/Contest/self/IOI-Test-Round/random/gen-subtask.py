#!/usr/bin/env pypy

from os import system as sh

def gen(idx, n, m, CMAX):
    print "(info) Generating data/random%s.in..." % idx
    sh("./random-gen.py %s %s %s > data/random%s.in" % (n, m, CMAX, idx))
    print "(info) Generating data/random%s.ans..." % idx
    sh("./a.out < data/random%s.in > data/random%s.ans" % (idx, idx))

sh("g++ random.cpp -O3 -Wno-unused-result")

MOD = 10**9 + 7

# Subtask 1 [1 - 10] 13pts
gen(1, 3, 3, 10)
gen(2, 4, -1, 10)
gen(3, 4, 2, 10)
gen(4, 4, -1, MOD)
gen(5, 6, 3, MOD)
gen(6, 6, -1, MOD)
gen(7, 6, -1, 10)
gen(8, 6, 15, 100)
gen(9, 6, 10, MOD)
gen(10, 5, 9, MOD)

# Subtask 2 [11 - 13] 4pts
gen(11, 10, 8, MOD)
gen(12, 10, 20, MOD)
gen(13, 10, -1, MOD)

# Subtask 3 [14 - 20] 8pts
gen(14, 15, 30, MOD)
gen(15, 20, 100, 2333)
gen(16, 30, -1, MOD)
gen(17, 30, 0, MOD)
gen(18, 30, 1, 2)
gen(19, 30, 400, MOD)
gen(20, 30, 300, MOD)

# Subtask 4 [21 - 23] 17pts
gen(21, 40, 22, MOD)
gen(22, 40, -1, MOD)
gen(23, 40, 700, MOD)
gen(23, 40, 673, MOD)

# Subtask 5 [24 - 28] 23pts
gen(24, 50, 23, MOD)
gen(25, 50, -1, MOD)
gen(26, 50, 1100, MOD)
gen(27, 50, 1203, MOD)
gen(28, 50, 666, MOD)

# Subtask 6 [29 - 40] 35pts
gen(29, 60, 58, MOD)
gen(30, 60, 1699, MOD)
gen(31, 60, -1, MOD)
gen(32, 60, 1743, MOD)
gen(33, 60, -1, MOD)
gen(34, 60, 1643, MOD)
gen(35, 60, -1, MOD)
gen(36, 60, 1763, MOD)
gen(37, 60, -1, MOD)
gen(38, 60, 1254, MOD)
gen(39, 60, -1, MOD)
gen(40, 60, 512, 1)
