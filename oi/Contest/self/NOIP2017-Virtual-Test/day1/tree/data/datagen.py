#!/usr/bin/env pypy

from os import system as sh

def gen(idx, n, q, d):
    print "(info) Generating 'tree%s.in'..." % idx
    sh("./gen.py %s %s %s > tree%s.in" % (n, q, d, idx))
    print "(info) Generating 'tree%s.ans'..." % idx
    sh("./a.out < tree%s.in > tree%s.ans" % (idx, idx))

gen(1, 1000, 1, 50)
gen(2, 10**5, 1, 75)
gen(3, 988, 1000, 100)
gen(4, 1000, 1000, 20)
gen(5, 10**5, 10**5, 1)
gen(6, 10**5, 10**5, 1)
gen(7, 10**5, 10**5, 60)
gen(8, 10**5, 10**5, 50)
gen(9, 10**5, 10**5, 40)
gen(10, 10**5, 10**5, 30)
