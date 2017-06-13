#!/usr/bin/env pypy

from os import system as sh

def gen(n, mode, limit, idx):
    for i in idx:
        print "(info) Generating 'satellite%s.in'..." % i
        sh("echo %s %s %s > satellite%s.in" % (n, mode, limit, i))
        sh("touch satellite%s.out" % i)

def gen_chain(n, limit, idx):
    for i in idx:
        print "(info) Generating 'satellite%s.in'..." % i
        sh("./chain-gen.py %s %s" % (n, limit) + " > satellite%s.in" % i)
        sh("touch satellite%s.out" % i)

def val(l, r):
    return range(l, r + 1)

# Subtask 1 [1-6]
gen(1, 0, 2000, [1])
gen(9, 0, 2000, [2])
gen(10, 0, 2000, [3])
gen(10, 1, 2000, [4])
gen(10, 2, 2000, [5])
gen_chain(10, 2000, [6])

# Subtask 2 [7-17]
gen(49, 0, 2500, val(7, 9))
gen(50, 0, 2500, val(10, 13))
gen(50, 0, 2500, [14])
gen(50, 1, 2500, [15])
gen(50, 2, 2500, [16])
gen_chain(50, 2500, [17])

# Subtask 3 [18-37]
gen(97, 0, 1900, val(18, 20))
gen(100, 0, 1900, val(21, 23))
gen(100, 1, 1900, val(24, 25))
gen(100, 2, 1900, val(26, 27))
gen_chain(100, 1900, val(28, 30))
gen(100, 0, 1900, val(31, 37))

# Subtask 4 [38-70]
gen(100, 0, 1425, val(38, 54))
gen(100, 1, 1425, val(55, 59))
gen(100, 2, 1425, val(60, 65))
gen_chain(100, 1425, val(66, 70))
