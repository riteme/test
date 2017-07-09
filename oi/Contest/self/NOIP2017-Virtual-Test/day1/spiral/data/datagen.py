#!/usr/bin/env pypy

from os import system as sh

def gen(idx, n):
    print "(info) Generating 'spiral%s.in'..." % idx
    sh("./gen.py %s > spiral%s.in" % (n, idx))
    print "(info) Generating 'spiral%s.ans'..." % idx
    sh("./a.out < spiral%s.in > spiral%s.ans" % (idx, idx))

gen(1, 4)
gen(2, 9)
gen(3, 9)
gen(4, 100)
gen(5, 998)
gen(6, 1000)
gen(7, 89999)
gen(8, 100000)
gen(9, 1000000)

print "(info) Generating 'spiral10.in'..."
with open("spiral10.in", "w") as writer:
    writer.write("1000000\n")
    writer.write("2 1 ")
    for i in xrange(3, 10**6 + 1):
        writer.write(str(i) + " ")

print "(info) Generating 'spiral10.ans'..."
sh("./a.out < spiral10.in > spiral10.ans")
