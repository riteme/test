#!/usr/bin/env pypy

from os import system as sh

def gen(idx, n, m, CMAX):
    print "(info) Generating 'run%s.in'..." % idx
    sh("./gen.py %s %s %s > run%s.in" % (n, m, CMAX, idx))
    print "(info) Generating 'run%s.ans'..." % idx
    sh("./a.out < run%s.in > run%s.ans" % (idx, idx))

gen(1, 8, 18, 50)
gen(2, 9, 6, 100)
gen(3, 10, 18, 100)
gen(4, 17, 17, 100)
gen(5, 20, 15, 5)
gen(6, 592, 20, 100)
gen(7, 9998, 19, 100)
gen(8, 43999, 19, 100)
gen(9, 98773, 20, 100)
gen(10, 100000, 20, 100)
